#include "OSInstantiation.h"

#include <string.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#if (defined WINDOWS) || (defined QNX)
#include <sys/stat.h>
#if (defined WINDOWS)
#include <direct.h>
#elif (defined ASTRA)
#include <unistd.h>
#endif
#endif

#include "ProgramMode.h"
#include "HAirFAL.h"
#include "EAir.h"
#include "TAir.h"

#include "OSLibFacilitiesAccomodation.h"

namespace PTPV
{

namespace air
{
	
#ifndef BORLAND
#define PRINT_T(X, Y) \
	{\
	const ios_base::fmtflags fmtflags0 = (Y).flags();\
	const streamsize prec0 = (Y).precision();\
	(Y) << fixed << setprecision(2);\
	X\
	(Y).flags(fmtflags0);\
	(Y) << setprecision(prec0);\
	}
#else
#define PRINT_T(X, Y) \
	{\
   X\
   }
#endif
	
#define CUT_T(t) \
	(static_cast <long int>(t) % 1000 + (t) - static_cast <long int>(t) )
	
#if (defined WINDOWS) || (defined QNX)
#define MKFNAME(NAME, EXT, UNICNAME) \
	char filename[8 + 10];	/* формируемое имя файла */\
	{\
	enum {MAXFNAMES = 65536};	/* максимальное число имён файлов */\
	struct stat buffer;\
	/* если размеры имени либо расширения файла превышают границы, */\
	/* обеспечиваем выход с ошибкой */\
	unsigned int n = MAXFNAMES * (strlen(NAME) > 8 || strlen(EXT) > 3);\
	strcpy_s(filename, sizeof(filename), (NAME));\
	do\
	{\
		char ns[6];	/* строковое представление n */\
		ns[5] = '\0';\
		filename[strlen(NAME)] = '\0';\
		/* получаем имя файла в формате AirRes<n>.txt */\
		/* (<n> - значение переменной n) */\
		strcat_s(filename, sizeof(filename), (sprintf_s(ns, sizeof(ns), "%u", n), ns));\
		strcat_s(filename, sizeof(filename), ".");\
		strcat_s(filename, sizeof(filename), (EXT));\
		n++;\
	}\
	/* выходим из цикла, если в текущем каталоге нет файла*/\
	/* с именем AirRes<n>.txt или есть файлы со всеми возможными именами */\
	while ( !stat(filename, &buffer) && n < MAXFNAMES + 1 );\
	(UNICNAME) = ( n < MAXFNAMES + 1 ) ? filename : 0;\
	}
#else
#define MKFNAME(NAME, EXT, UNICNAME) \
	char filename[8 + 10];	/* формируемое имя файла */\
	if (strlen(NAME) > 8 || strlen(EXT) > 3)\
		(UNICNAME) = 0;\
	else\
	{\
		enum {MAXFNAMES = 65536};	/* максимальное число имён файлов */\
		char *ts;	/* указатель на строковое представление t */\
		strncpy(filename, (NAME), 9);\
		ts = filename + strlen(filename);\
		sprintf(ts, "%i", static_cast <int>(time(NULL)) % MAXFNAMES);\
		strncat(strcat(filename, "."), (EXT), 3);\
		(UNICNAME) = filename;\
	}

#endif

struct TAir::TMsgProc : public air::TMsgProc
{
	TMsgProc() {}
	
	static const TMsgProc CMsgProc0;
}; // struct TMsgProc
	
struct TAir::TStateProc : public air::TStateProc
{
	TStateProc() {}

	static const TStateProc CStateProc0;
}; // struct TStateProc


TAir::TAir(TZone monitoredZones[ZONE_MAX])
    : TrcProc(GeneralTrack, Link, SensorDescription), PrognProc(GeneralTrack),
      ZoneProc(GeneralTrack, monitoredZones), MsgsForm(GeneralTrack)
{
	int recordSize;
	unsigned int i, j;
	// создание зоны характеристик источников
	recordSize = sizeof(TSensorDescription) * (SENS_MAX + 1);
	memset(&SensorDescription, 0, recordSize);
	
	// Заполнение характеристик источников по ВО.
	SensorDescription[USENS_CP_45L6].dataTemp = 10.;   
	SensorDescription[USENS_CP_45L6].trackCount = 500;
	SensorDescription[USENS_CP_45L6].maxTrackNumber = 500;
	for ( i = USENS_CP_99SH6_N1; i <= USENS_CP_99SH6_N2; i++ )
	{
		SensorDescription[i].dataTemp = 10.;   
		SensorDescription[i].trackCount = 400;
		SensorDescription[i].maxTrackNumber = 400;
	} // for
	// Тимчасово.
	SensorDescription[USENS_CP_MULTI].dataTemp = 30.;   
	SensorDescription[USENS_CP_MULTI].trackCount = 500;
	SensorDescription[USENS_CP_MULTI].maxTrackNumber = 500;
	
	// формирование зоны связи трасс источников с обобщённой трассой
	for ( i = 0; i <= SENS_MAX; i++ )
	{
		Link[i] =new TSensGenTrcLink[(SensorDescription[i].maxTrackNumber + 1)];
		for( j = 0; j <= SensorDescription[i].maxTrackNumber; j++ )
		{
			// чистка зоны связи трасс источников с обобщённой трассой
			Link[i][j].genTrc = 0;
			Link[i][j].identState = IS_NONE;
		}
	}
	
	for ( i = 1; i <= UGEN_TRC_MAX; i++ )
	{
		// чистка зоны обобщённых трасс
		GeneralTrack[i] = CGenTrcS0;
	}
	GeneralTrack.Init();
		
	// Инициализация диспетчера задач НУМ
	num.Init(SensorDescription, &GeneralTrack, Link,
	         ":/fileIvo.xml", ":/fileTvo.xml");
	
#ifndef BORLAND
	 const TRes res = {GeneralTrack};
	 pres = new TRes(res);
#else
	pres = new TRes(GeneralTrack, Grp);
#endif
	
	OFInit();
	printNum = 0;
} // TAir()

TAir::~TAir() 
{
	OFCleanup();
	
	delete pres;
	  
	int i;
	for (i=0; i <= SENS_MAX; i++ )
	{
		delete[] Link[i];
    }
} // ~TAir()

TAir::operator const TAir::TRes &() const
{
	return *pres;
} // operator const TRes &()

const TAir::TRes &TAir::GetMsg(const TUTrcMsg &Msg, double T,
                               TMsgFormSet *pmsgFormSet,
                               PTPV_TGenTrcMsg *pGenTrcMsg)
{
#ifdef TESTING
#ifdef WINDOWS
	AssignTextAttributes0();
#endif
	// Технологическая печать входных данных.
    *this << "\nTAir::GetMsg started ...                   {"
		<< ++printNum << "}\n";
 	PrintTrcMsg(Msg);
#endif // ifdef TESTING
	
	// Организация зоны информационных ситуаций обработки
	TMsgProc msgProc = TMsgProc::CMsgProc0;
	
	// Вызов местного диспетчера задач третичной обработки сообщений.
	TrcProc.MsgTaskChain(Msg, T, &msgProc);
    // Вызов местного диспетчера задач НУМ по сообщениям.
    num.MsgTaskChain(Msg, &msgProc);
    // Вызов местного диспетчера задач экстраполяции координат по сообщениям.
	PrognProc.MsgTaskChain(&msgProc);
	// Вызов местного диспетчера задач расчёта попадания объекта в зоны,
	// производимого по сообщениям.
	ZoneProc.MsgTaskChain(&msgProc);
	// Формирование результатов обработки сообщения потребителям.
	MsgsForm(Msg.sensNum, Msg, T, &msgProc, pGenTrcMsg, pmsgFormSet);
	
#ifdef TESTING
	// Технологическая печать выходных данных.
	for ( int i = 0; i < 2; i++ )
	{
		if ( pmsgFormSet->genTrcMsg[i] )
			// *this <= "i = " <= i <= "\n";
			PrintGenTrcMsg(pGenTrcMsg[i]);
	} // for
#endif // ifdef TESTING
	
	return *pres;
} // GetMsg()
	
// Корректировка статуса трассы
const TAir::TRes &TAir::TrcStateCheck(const double T, TMsgFormSet *pmsgFormSet,
	                                  PTPV_TGenTrcMsg *pGenTrcMsg,
                                      TAir::fGiveResult fpResult)
{
#ifdef TESTING
#ifdef QNX
 	 PRINT_T(*this < "\nTAir::TrcStateCheck started at " < T < " c... \n";, ofile)
#else
	 PRINT_T(PRINT_T(*this << "\nTAir::TrcStateCheck started at " << T << " c... \n";, ofile), cout)
#endif 
#endif // ifdef TESTING
	
	// Организация зоны информационных ситуаций обработки
	TStateProc stateProc = TStateProc::CStateProc0;
		 
	bool stateTaskStart = true;
	for (int genTrcNum = 1; genTrcNum <= UGEN_TRC_MAX; genTrcNum++ )
	{
		// Если формуляр не занят, переход к следующему.
		if ( GeneralTrack[genTrcNum].genTrcT.busyState == EU_NO )
			continue;
		stateProc = TStateProc::CStateProc0;
		stateProc.genTrcNum = genTrcNum;
		// Обращение к местному диспетчеру задач третичной обработки по
		// периодическому контролю статуса трасс с возвращением
		// решений относительно stateProc.genTrcNum.
		TrcProc.StateTaskChain(stateTaskStart, T, &stateProc);
		// Вызов местного диспетчера задач НУМ по
		// периодической проверке трассы stateProc.genTrcNum.
        num.StateTaskChain(&stateProc);
		// Вызов местного диспетчера задач период-ской экстраполяции координат.
		PrognProc.StateTaskChain(&stateProc);
		// Вызов местного диспетчера задач периодического расчёта попадания в
		// зоны объекта, описываемого трассой stateProc.genTrcNum.
		ZoneProc.StateTaskChain(&stateProc);
		// Формирование результатов периодической обработки потребителям
		// относительно трассы stateProc.genTrcNum.
		MsgsForm(T, &stateProc, 0, pGenTrcMsg, pmsgFormSet);
	
#ifdef TESTING
	// Технологическая печать выходных данных.
	if ( pmsgFormSet->genTrcMsg[0] )
		// *this <= "i = " <= i <= "\n";
		PrintCheckGenTrcMsg(pGenTrcMsg[0]);
#endif // ifdef TESTING
			 
		// Возвращение результатов периодической обработки потребителям
		// относительно трассы stateProc.genTrcNum
		fpResult();
			
		stateTaskStart = false;  
	} // for (genTrcNum)
	
	return *pres;
} // TrcStateCheck()

// Печать информации по отработке ТОИ в файл
TAir &TAir::operator <(const char *const pMsg)
{
	ofile << pMsg;
	return *this;
}
TAir &TAir::operator <(const char symbol)
{
	ofile << symbol;
	return *this;
}
TAir &TAir::operator <(const int num)
{
	ofile << num;
	return *this;
}
TAir &TAir::operator <(const double number)
{
	ofile << number;
	return *this;
}
TAir &TAir::operator <(const TUTrcMsg &TrcMsg)
{
	FPrintTrcMsg(TrcMsg);
	return *this;
} // временно!!!
TAir &TAir::operator <(const PTPV_TGenTrcMsg &GenTrcMsg)
{
	if ( GenTrcMsg.trcState )
		FPrintGenTrcMsg(GenTrcMsg);
	return *this;
} // временно!!!

#ifndef QNX
// Печать информации по отработке ТОИ на экран и в файл
TAir &TAir::operator <=(const char *const pMsg)
{
	cout << pMsg;
	ofile << pMsg;
	return *this;
}
TAir &TAir::operator <=(const char symbol)
{
	cout << symbol;
	ofile << symbol;
	return *this;
}
TAir &TAir::operator <=(const int number)
{
	cout << number;
	ofile << number;
	return *this;
}
TAir &TAir::operator <=(const double value)
{
	cout << value;
	ofile << value;
	return *this;
}
#endif

// Печать информации по отработке ТОИ на те устойства, куда это возможно
TAir &TAir::operator <<(const char *const pMsg)
{
#ifndef QNX
	cout << pMsg;
#endif
	ofile << pMsg;
	return *this;
}
TAir &TAir::operator <<(const char symbol)
{
#ifndef QNX
	cout << symbol;
#endif
	ofile << symbol;
	return *this;
}
TAir &TAir::operator <<(const int number)
{
#ifndef QNX
	cout << number;
#endif
	ofile << number;
	return *this;
}
TAir &TAir::operator <<(const double value)
{
#ifndef QNX
	cout << value;
#endif
	ofile << value;
	return *this;
}

#ifndef QNX
// Печать на экран информации по входному сообщению
void TAir::SPrintTrcMsg(const TUTrcMsg &Msg)
{
	printTrcMsg(Msg, cout);
}
#endif

// Печать в файл информации по входному сообщению
void TAir::FPrintTrcMsg(const TUTrcMsg &Msg)
{
	printTrcMsg(Msg, ofile);
}

// Печать на доступные устройства информации по входному сообщению
void TAir::PrintTrcMsg(const TUTrcMsg &Msg)
{
#ifndef QNX
	SPrintTrcMsg(Msg);
#endif
	FPrintTrcMsg(Msg);
}

#ifndef QNX
// Печать на экран информации по выходному сообщению
void TAir::SPrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
	printGenTrcMsg(Msg, cout);
}
#endif

// Печать в файл информации по выходному сообщению
void TAir::FPrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
	printGenTrcMsg(Msg, ofile);
}

// Печать на доступные устройства информации по выходному сообщению
void TAir::PrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
#ifndef QNX
	SPrintGenTrcMsg(Msg);
#endif
	FPrintGenTrcMsg(Msg);
}

#ifndef QNX
// Печать на экран информации по выходному сообщению на периодике
void TAir::SPrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
	printCheckGenTrcMsg(Msg, cout);
}
#endif

// Печать в файл информации по выходному сообщению на периодике
void TAir::FPrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
	printCheckGenTrcMsg(Msg, ofile);
}

// Печать на доступные устройства информации по выходному сообщению на периодике
inline void TAir::PrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg)
{
#ifndef QNX
	SPrintCheckGenTrcMsg(Msg);
#endif
	FPrintCheckGenTrcMsg(Msg);
}

// Подготовка к печати информации в файл 
int TAir:: OFInit()
{
#if (defined WINDOWS) || (defined QNX)
	const char resFolder[20] = "C:\\mniipa debug\\OUT";
	char currentFolder[256];
	_mkdir(resFolder);
	_getcwd(currentFolder, 256);
	_chdir(resFolder);
#endif

	char *unicName;
	MKFNAME("AirRes", "txt", unicName);
	if ( unicName == NULL )
	{
		perror("file name finding");
#if (defined WINDOWS) || (defined QNX)
		_chdir(currentFolder);
#endif
		return -2;
	}
	ofile.open(unicName, ios::out);
#if (defined WINDOWS) || (defined QNX)
	_chdir(currentFolder);
#endif
	if ( !ofile )
	{
		perror("open");
		return -1;
	}
	else
		ofile << " Results of an air targets data process." << endl  
		      << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			  << endl << endl;
	return 0;
}

// Завершение печати информации в файл
void TAir:: OFCleanup()
{
	ofile << endl << "====================================================="
		  << endl << "End of the run results.";
	ofile.close();
}
 
// Печать информации по входному сообщению
void TAir::printTrcMsg(const TUTrcMsg &Msg,
					   ostream & stream)
{
	stream << " ------------ Received -------------\n";
		stream << " TAir:: pMsg->\n";
	/** if ( Msg.msgType == EU_MT_PTPV_REPORT )
	{
		stream << "   ~it is REPORT~" << '\n'; 
		stream << "    genTrcNum = " << Msg.genTrcNum << '\n';
		stream << "    RSTrcNum = " << Msg.RSTrcNum << '\n';
	}
	else **/	 
	{
		stream << "    sensNum = " << static_cast <unsigned int>(Msg.sensNum)
		       << '\n';
		stream << "    trcNum = " << Msg.trcNum << '\n'; 
		stream << "    trcState = " << Msg.trcState; 
		 // индикация состояния сопровождения трассы
		 if ( Msg.trcState == EU_TS_NEW )
		 {
			 stream << " - ";
				#ifdef WINDOWS
				DownTextAttributes(FOREGROUND_GREEN);	// фиолетовый
				#endif
			 stream << "new";
				#ifdef WINDOWS
				SetTextAttributes0();
				#endif
		 }
		 else if ( Msg.trcState == EU_TS_END )
		 {
			 stream << " - ";
				#ifdef WINDOWS
				DownTextAttributes(FOREGROUND_RED);	// голубой
				#endif
			 stream << "end";
				#ifdef WINDOWS
				SetTextAttributes0();
				#endif
		 }
		stream << '\n'; 
		PRINT_T(stream << "    t = " << CUT_T(Msg.t) << "\n";, stream)
		stream << "    x = " << Msg.x << " +- " << Msg.trustXY << '\n'; 
		stream << "    y = " << Msg.y << " +- " << Msg.trustXY << '\n'; 
		stream << "    h = " << Msg.h;
		Msg.hUpdate ? stream << " +- " << Msg.trustH << '\n' :
		                stream << '\n';
		stream << "    hBar = " << Msg.hBar;
		Msg.hBarUpdate ? stream << " +- " << Msg.trustH << '\n' :
		                   stream << '\n';
		/* stream << "    flyInfState = " << static_cast <int>(Msg.flyInfState)
		       << ", " << "HBarLevel = "
		       << static_cast <int>(Msg.flyInf.levelHBar) << '\n';*/
		stream << "    v = " << Msg.v << '\n';
		stream << "    psi = " << Msg.psi << '\n';
			#ifdef WINDOWS
			DownTextAttributes(static_cast<WORD>((Msg.OGPUpdate &&
			(Msg.OGP == EU_OGP_MB_FRIEND || Msg.OGP == EU_OGP_FRIEND)) * MAGENTA |
			(Msg.OGPUpdate && Msg.OGP == EU_OGP_HOSTILE) * CYAN));
			#endif
		stream << "    " << ogpnames[Msg.OGP];
			#ifdef WINDOWS
			SetTextAttributes0();
			#endif
		stream << "\t   N`";
		Msg.indNum ? stream << Msg.indNum << '('
	       << lineNames[Msg.reqLine] << ')' : stream << "?\t";
		stream << '\t';
			#ifdef WINDOWS
			InvertTextAttributes(static_cast<WORD>(Msg.quantUpdate * (YELLOW | BACKGROUND_BLUE | BACKGROUND_RED)));	 // синий
			#endif
		stream << static_cast <unsigned int>(Msg.quant);
			#ifdef WINDOWS
			SetTextAttributes0();
			#endif
		stream << '\n';
		stream << "    ";
		(Msg.TO ? stream << static_cast <unsigned int>(Msg.TO) : stream << '?')
		       << " type of ";
		stream << classnames[Msg.objClass] << '\n';
		stream << "    index = " << static_cast <unsigned int>(Msg.IO) << '\n';
		///if ( Msg.identBlock == EU_YES )
		///{
		///	stream << "    ";
		///	stream << (Msg.identBlock == EU_YES ? "\t    Identblock" : "\0");
		///	/* stream << (Msg... == EU_YES ? ".." : "\0"); ...*/
		///	stream << '\n';
		///}
		!(Msg.xyUpdate) ? (stream << "    x and y are extrapolated\n", 0) : 0;
		!(Msg.hUpdate) ? (stream << "    h is extrapolated\n", 0) : 0;
		!(Msg.hBarUpdate) ? (stream << "    hBar is extrapolated\n", 0) : 0;
		/** // если поступили распоряжения
		struct TOrders
		{
			unsigned int : 0;
			unsigned char order;
			unsigned int : 0;
		};
		if ( static_cast <const TOrders *>(static_cast <const void *>(&Msg.setOrder))->order )
		{
			stream << "    Orders:";
				#ifdef WINDOWS
				UpTextAttributes(FOREGROUND_INTENSITY); // ярко-белый
				#endif
			stream << (Msg.setOrder.orderTypeTargObj ? "\tTargObj" : "\0");
			stream << (Msg.setOrder.orderTypeTargIF ? "\tTargIF" : "\0");
			stream << (Msg.setOrder.orderTypeChanTarg ? "\tChanTarg" : "\0");
			stream << (Msg.setOrder.orderTypeH ? "\tTypeH" : "\0");
			stream << (Msg.setOrder.orderTypeOGP ? "\tTypeOGP" : "\0");
				#ifdef WINDOWS
				SetTextAttributes0();
				#endif
			stream << '\n';
		} **/
	}
	/*stream << " header.msgType =  " << pGenTrcMsg[i].msgType << "\n";
	stream << " header.msgLength =  " << pGenTrcMsg[i].msgLength << "\n";*/
	stream << " ----------------------------------------- " << endl;
}

// Печать информации по выходному сообщению
void TAir::printGenTrcMsg(const PTPV_TGenTrcMsg &Msg,
						  ostream & stream)
{
	stream << '\n';
	stream << "TAir::GeneralizedTrack is updated:\n";
	stream <<  " ---------------Out-----------------\n";
	stream << " genTrcNum = " << Msg.genTrcNum;  
	if ( Msg.trc.sensCount > 0 )
		stream << ':';
	{
		for ( int j = 1; j < SENS_MAX; j++ )
			if ( Msg.trc.sensTrcNum[j] > 0 )
				stream << ' ' << j << '-' << Msg.trc.sensTrcNum[j]; 
	}
	stream << ',';
		#ifdef WINDOWS
		DownTextAttributes(FOREGROUND_RED);	// голубой
		#endif
	stream << (Msg.sensDelete == EU_YES ? " \t/SensDelete/" : "\0");
		#ifdef WINDOWS
		SetTextAttributes(MAGENTA_INTENS);	// ярко-фиолетовый
		#endif
	stream << (Msg.trcState == EU_TS_NEW ? " \t/NEW/" : "\0");
		#ifdef WINDOWS
		SetTextAttributes0();
		#endif
	stream << '\n';
	PRINT_T(stream << " t = " << CUT_T(Msg.trc.tXYUpdate) << ",\t/msgTime = " << CUT_T(Msg.msgTime) << "/\n";, stream)
	stream << " x = " << Msg.trc.x << " +- " << Msg.trc.trustXY << ",\n"; 
	stream << " y = " << Msg.trc.y << " +- " << Msg.trc.trustXY << ",\n"; 
	stream << " h = " << Msg.trc.h << ",\n"; 
	stream << " v = " << Msg.trc.v << ",\n"; 
	stream << " psi = " << Msg.trc.psi << '\n'; 
	stream << ' ' << ogpnames[Msg.trc.OGP];
	stream << "\t N`";
	Msg.trc.indNum ? stream << Msg.trc.indNum << '('
	       << lineNames[Msg.trc.reqLine] << ')' : stream << "?\t"; // ?
	                               
	stream << "    " << static_cast <unsigned int>(Msg.trc.quant);
	stream << '\n';
	stream << " ";
	(Msg.trc.TO ? stream << static_cast <unsigned int>(Msg.trc.TO)
	            : stream << '?') << " type of ";
	stream << classnames[Msg.trc.objClass];
	stream << '\n';
	stream << " index = " << static_cast <unsigned int>(Msg.trc.IO);
	/** if ( Msg.trc.chanTarg == EU_YES || Msg.trc.identBlock == EU_YES ||
	     Msg.trc.targCP == EU_YES ) */
	/** {
		stream << '\n';
		stream << ' ' << ( Msg.trc.chanTarg == EU_YES ? "Chantarg" : "\0");
		stream << ( Msg.trc.identBlock == EU_YES ? "\tIdentblock" : "\0");
		stream << ( Msg.trc.targCP == EU_YES ? "\t\tTargCP" : "\0");
		const short &grpNum = Msg.trc.grpInfo.num;
		stream << "\t (",
		Msg.genTrcNum == Msg.trc.grpInfo.leadTrcNum ?
		   stream << 'L' << grpNum << '-'
		          << static_cast <int>(Msg.trc.grpInfo.trcCount) :
		   stream << grpNum,
		stream << ')';
	} **/
	stream << ".\n";
	//stream << "tMsg = " <<  Msg.tMsg << ".\n";
	stream << " - - - - - - - - - - - - - - - - - - - -" << endl;
}

// Печать информации по выходному сообщению на периодике
void TAir::printCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg,
							   ostream & stream)
{
	stream << '\n';
	stream << "TAir::GeneralizedTrack is updated:\n";
		#ifdef WINDOWS
		SetTextAttributes(FOREGROUND_RED);	// красный
		#endif
	stream << (Msg.trcState == EU_TS_END ? "\tdeleted:\n" : "\0");
		#ifdef WINDOWS
		SetTextAttributes0();
		#endif
	stream <<  " -----------------Out------------------\n";
	stream << " genTrcNum = " << Msg.genTrcNum; 
	if ( Msg.trc.sensCount > 0 )
	{
		stream << ':';
		for ( int j = 1; j < SENS_MAX; j++ )
			if ( Msg.trc.sensTrcNum[j] > 0 )
				stream << ' ' << j << '-' << Msg.trc.sensTrcNum[j]; 
	}
	stream << ',';
		#ifdef WINDOWS
		DownTextAttributes(FOREGROUND_RED);	// голубой
		#endif
	stream << (Msg.sensDelete == EU_YES ? " \t/SensDelete/" : "\0");
		#ifdef WINDOWS
		SetTextAttributes(CYAN_INTENS);		// ярко-голубой
		#endif
	stream << (Msg.trcState == EU_TS_END ? " \t/END/" : "\0");
		#ifdef WINDOWS
		SetTextAttributes0();
		#endif
	stream << '\n';
	PRINT_T(stream << " t = " << CUT_T(Msg.trc.tXYUpdate) << ",\t/msgTime = " << CUT_T(Msg.msgTime) << "/\n";, stream)
	stream << " x = " << Msg.trc.x
	       << ",\t/xProgn = " << Msg.trc.progn.x << "/\n"; 
	stream << " y = " << Msg.trc.y
	       << ".\t/yProgn = " << Msg.trc.progn.y << "/\n"; 
	stream << " - - - - - - - - - - - - - - - - - - - -" << endl;
}

#ifdef WINDOWS
int TAir::AssignTextAttributes0()
{
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	return !GetConsoleScreenBufferInfo(console, &sattributes0);
}

inline int TAir::SetTextAttributes0()
{
	return !SetConsoleTextAttribute(console, sattributes0.wAttributes);
}

inline int TAir::SetTextAttributes(WORD sattributes)
{
	return !SetConsoleTextAttribute(console, sattributes);
}

int TAir::UpTextAttributes(WORD sattributes)
{
	CONSOLE_SCREEN_BUFFER_INFO sattribold;
	GetConsoleScreenBufferInfo(console, &sattribold);
	return !SetConsoleTextAttribute(console, sattribold.wAttributes | sattributes);
}
int TAir::DownTextAttributes(WORD sattributes)
{
	CONSOLE_SCREEN_BUFFER_INFO sattribold;
	GetConsoleScreenBufferInfo(console, &sattribold);
	return !SetConsoleTextAttribute(console,
   	static_cast<WORD>(sattribold.wAttributes & ~sattributes));
}
int TAir::InvertTextAttributes(WORD sattributes)
{
	CONSOLE_SCREEN_BUFFER_INFO sattribold;
	GetConsoleScreenBufferInfo(console, &sattribold);
	return !SetConsoleTextAttribute(console, sattribold.wAttributes ^ sattributes);
}


// консоль стандартного вывода
HANDLE TAir::console = NULL;
// атрибуты стандартного вывода
CONSOLE_SCREEN_BUFFER_INFO TAir::sattributes0; 
#endif

const TAir::TMsgProc TAir::TMsgProc::CMsgProc0;

const TAir::TStateProc TAir::TStateProc::CStateProc0;

const char *TAir::ogpnames[5] = {"NEOPOGN", "CHUGOY", "SVOY", "GARANT SVOY"};

const char *TAir::classnames[5] = {"ufo", "air", "sea", "ground", "surface"};

const char *TAir::lineNames[10] = {"--", "at", "rbs", "pw", "mk", "rb", "tc",
                             "id", "ds"};


#ifdef BORLAND
TAir::TRes::TRes (const TGeneralTrack &GenTrack, const TTrackGrp &TrackGrp)
                 : GeneralTrack (GenTrack), Grp(TrackGrp) 
{
}
#endif

} // namespace air

} // namespace PTPV
