#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "S_E_Num.h"

/// #include <QList>
/// #include <QtXml>

namespace N_U_M
{

//диспетчер чтения таблиц ИВО и ТВО
class DispatcherTable
{
public:
    DispatcherTable();

    TableIvo* ReadIvo(const char* fileIvo);             //Чтение xml-файла с таблицей ИВО
    TableTvo* ReadTvo(const char* fileTvo);             //Чтение xml-файла с таблицей ТВО
    TableIvoTvo* ReadIvoTvo(const char* fileIvoTvo);    //Чтение xml-файла противоерчий ИВО-ТВО

};
}
#endif // FILEHANDLER_H
