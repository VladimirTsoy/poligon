/******************************************************
 * Файл сгенирирован XML_DSS компилятором
 * Назначение: Объявления пользовательских типов, заданного модуля
 * Имя файла:  /home/user/qt/Poligon/POLIGON02/../import/Message_DDS/include/Message.h
 * Имя XML-файла (источник): /home/user/qt/Poligon/POLIGON02/RDDS_TGenMsg/import/xml/Message.xml
 * Дата создания: 28.12.20 04:15:01 UTC
 * РСРД 0.1
 * Copyright (c) ОАО "НПО РусБИТех"
 ******************************************************/
#ifdef WIN32
#pragma warning(disable: 4100)
#endif
#ifndef RBT_MESSAGE_H
#define RBT_MESSAGE_H
#include <r_dds/core/Exception.hpp>
#include <cstdint>
#include <array>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include "rdds_pack.h"
#ifndef RBT_ENUM_CPP11
#define RBT_ENUM_CPP11
#endif
namespace Message  {
  

  /******************************************************
   * Предварительное объявление классов и их алиасов
   ******************************************************/
  class command_str;
  class TGenTcrMsg;
  

  

    /******************************************************
     * Объявления нумераторов
     ******************************************************/
  
  #ifdef RBT_ENUM_CPP11
    /**
    * @enum EUTrcState
    * @brief Принзнак состояния сопровождения трассы
    */
    enum class EUTrcState : int16_t {
      EU_TS_NEW = 1,
      EU_TS_TRK = 2,
      EU_TS_END = 3
    };
    /**
    * @enum EUYesNo
    * @brief Тип информации (да - нет)
    */
    enum class EUYesNo : int16_t {
      EU_NO  = 0,
      EU_YES = 1
    };
    /**
    * @enum SENS_MAX
    * @brief 
    */
    enum class SENS_MAX : int32_t {
      SENS_MAX = 6
    };
    /**
    * @enum EUOGP
    * @brief Результат опознования гос принадлежности
    */
    enum class EUOGP : int32_t {
      EU_OGP_UNKNOW    = 0,
      EU_OGP_HOSTILE   = 1,
      EU_OGP_MB_FRIEND = 2,
      EU_OGP_FRIEND    = 3,
      EU_OGP_MAX       = 4
    };
    /**
    * @enum command_enum
    * @brief Для отправки команды старт или стоп
    */
    enum class command_enum : int32_t {
      Start = 0,
      Stop  = 1
    };
  #else
    struct EUTrcState_def  {
      enum type : int16_t {
        EU_TS_NEW = 1,
        EU_TS_TRK = 2,
        EU_TS_END = 3
      };
    };
    typedef dds::core::safe_enum< EUTrcState_def > EUTrcState;
    struct EUYesNo_def  {
      enum type : int16_t {
        EU_NO  = 0,
        EU_YES = 1
      };
    };
    typedef dds::core::safe_enum< EUYesNo_def > EUYesNo;
    struct SENS_MAX_def  {
      enum type : int32_t {
        SENS_MAX = 6
      };
    };
    typedef dds::core::safe_enum< SENS_MAX_def > SENS_MAX;
    struct EUOGP_def  {
      enum type : int32_t {
        EU_OGP_UNKNOW    = 0,
        EU_OGP_HOSTILE   = 1,
        EU_OGP_MB_FRIEND = 2,
        EU_OGP_FRIEND    = 3,
        EU_OGP_MAX       = 4
      };
    };
    typedef dds::core::safe_enum< EUOGP_def > EUOGP;
    struct command_enum_def  {
      enum type : int32_t {
        Start = 0,
        Stop  = 1
      };
    };
    typedef dds::core::safe_enum< command_enum_def > command_enum;
  #endif
  

  

    /******************************************************
     * Объявления типов контейнеров и их алиасов
     ******************************************************/
  typedef std::array <int32_t,6 > ArrayTrcNum; /**< Массив номеров трасс от источников сопровождения. Индекс элемента массива соотв. номеру источника  */
  typedef std::array <int16_t,5 > ArrZone; /**< Максимальное количество зон специального района */
  typedef std::array <bool,5 > ArrZoneProgn; /**< Зоны специального района */
  

  /******************************************************
   * Объявления классов (структур)
   ******************************************************/
  /**
  * @class Message::command_str
  * @brief 
  * @author AUTOGENERATE
  * @date Mon Dec 28 16:15:01.417 2020
  */
  class command_str {
    public:
      static const char* nameOfType;
      /**
      * @brief Конструктор из упакованного представления (всего объекта или ключей).
      * @param from_buf Буфер, содержащий упакованные данные.
      *                 Если буфер содержит только ключи, то всем не ключевым полям
      *                 присваиваиваются значения по умолчанию.
      * @param lenbuf   Длинна буфера в байтах.
      * @param key_only \li если true  - буфер содержит только упакованные ключи
      *                 \li если false - буфер содержит только упаковку всего объекта
      */
      command_str(const void* from_buf, unsigned lenbuf, bool key_only = false);
      
      /**
      * @brief Ничего не делает. 
      * @return Возвращает Hash сделанный конструктором по умолчанию!
      */
      inline r_dds::dds::KeyHash_t keyHash() const {
        r_dds::dds::KeyHash_t ret;
        return ret;
      }
      /**
      * @brief Запрос наличия ключевых полей
      * @return false
      */
      static bool hasKey() { return false;}
      
      #ifndef WIN32
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wunused-parameter"
      #endif
      
      /**
      * @brief Ничего не делает. 
      * @return true
      */
      inline bool keyEqual(const command_str& ) const { return true;}
      /**
      * @brief Ничего не делает. 
      * @return true
      */
      inline bool keyEqual(const void* , unsigned , bool key_only = false) const { return true; }
      /**
      * @brief Ничего не делает. 
      * @return true
      */
      inline static bool keyEqual(const void* , unsigned , const void* , unsigned , bool key_only = false ) { return true; } 
      
      #ifndef WIN32
      #pragma GCC diagnostic pop
      #endif
      
      /**
      * @brief Ничего не делает. 
      * @return ноль (0)
      */
      unsigned lenPacked() const;
      /**
      * @brief Ничего не делает. 
      * @return ноль (0)
      */
      static unsigned maxlenPacked();
      /**
      * @brief Ничего не делает. 
      * @return ноль (0)
      */
      inline unsigned keylenPacked() const { return 0; }
      /**
      * @brief Упаковка объекта в буфер
      * @param[in] to_buf Буфер, в который идет упаковка
      * @param[in] lenbuf Размер буфера
      * @return длина упаковки, 0 если буфер мал
      */
      unsigned pack(void* to_buf, unsigned lenbuf) const;
      /**
      * @brief Ничего не делает. 
      * @return ноль (0)
      */
      inline unsigned packKey(void* , unsigned ) const { return 0; }
      /**
      * @brief Распаковка объекта из буфера
      * @param[in] from_buf Буфер, содержащий упаковку
      * @param[in] lenbuf Размер буфера
      * @return признак успеха
      */
      bool unpack(const void* from_buf, unsigned lenbuf);
      /**
      * @brief Ничего не делает. 
      * @return true
      */
      inline bool unpackKey(const void* , unsigned ) { return true; }
      /**
      * @brief Конструктор по умолчанию
      */
      command_str() {
        m_command = Message::command_enum::Start;
      }
      /**
      * @brief Явный конструктор
      */
      explicit command_str(
        command_enum command) :
          m_command(command) {}
  
      /**
      * @brief Конструктор копирования
      */
      inline command_str (command_str const & other) {
        m_command = other.m_command;
      }
      /**
      * @brief Конструктор перемещения
      */
      inline command_str (command_str && other) {
        m_command = std::move(other.m_command);
      }
      /**
      * @brief Оператор копирования
      */
      inline command_str& operator = (command_str const & other) {
        if (this != &other) {
          m_command = other.m_command;
        }
        return *this;
      }
      /**
      * @brief Оператор перемещения
      */
      inline command_str& operator = (command_str && other) {
        if (this != &other) {
          m_command = std::move(other.m_command);
        }
        return *this;
      }
      /**
      * @brief Оператор сравнения ==
      * @param[in]  other константная ссылка на сравниваемый объект
      * @return  true если параметры одинаковы
      */
      inline bool operator == (const command_str& other) const {
        if (this != &other) {
          return
            m_command == other.m_command;
        }
        return true;
      }
  
      /**
      * @brief Оператор сравнения ==
      * @param[in]  other константная ссылка на сравниваемый объект
      * @return  true если параметры не одинаковы
      */
      inline bool operator != (const command_str& other) const {
        return !(*this == other);
      }
  
      /**
      * @brief Задание значения полю m_command
      * @param[in] value Задаваемое значение типа command_enum
      */
      inline void command(command_enum value) {
        m_command= value;
      }
  
      /**
      * @brief Получение значения поля m_command
      * @return Значение поля m_command типа command_enum
      */
      inline command_enum command() const {
        return m_command;
      }
  
      /**
      * @brief Получение ссылки на поле m_command
      * @return Ссылка на поле m_command типа command_enum
      */
      inline command_enum& command() {
        return m_command;
      }
  
      /**
      * @name Атрибуты класса
      * @{
      */
      command_enum m_command;
      /**
      * @}
      */
  };
  /**
  * @class Message::TGenTcrMsg
  * @brief 
  * @author AUTOGENERATE
  * @date Mon Dec 28 16:15:01.417 2020
  */
  class TGenTcrMsg {
    public:
      static const char* nameOfType;
      /**
      * @brief Конструктор из упакованного представления (всего объекта или ключей).
      * @param from_buf Буфер, содержащий упакованные данные.
      *                 Если буфер содержит только ключи, то всем не ключевым полям
      *                 присваиваиваются значения по умолчанию.
      * @param lenbuf   Длинна буфера в байтах.
      * @param key_only \li если true  - буфер содержит только упакованные ключи
      *                 \li если false - буфер содержит только упаковку всего объекта
      */
      TGenTcrMsg(const void* from_buf, unsigned lenbuf, bool key_only = false);
      /**
      * @brief Запрос наличия ключевых полей
      * @return true, если для типа определены ключевые поля, иначе false
      */
      static bool hasKey() { return true;}
      /**
      * @brief Запрос хеш-кода ключевых полей\n
      *        Возвращает хеш-код для набора ключевых полей.
      * @return Хеш-код.
      */
      r_dds::dds::KeyHash_t keyHash() const; 
      /**
      * @brief Проверка совпадения значений ключевых полей двух объектов
      * @param[in] object Экземпляр данных для сравнения
      * @return true, если значения ключевых полей объектов равны
      */
      bool keyEqual(const TGenTcrMsg& object) const;
      /**
      * @brief Проверка совпадения значений ключевых полей двух объектов
      * @param[in] buf Буфер с упакованными данными объекта для сравнения
      * @param[in] lenbuf Размер буфера
      * @param[in] key_only Если true, буфер содержит только упаковку ключевых данных, иначе весь объект
      * @return true, если значения ключевых полей объектов равны
      */
      bool keyEqual(const void* buf, unsigned lenbuf, bool key_only = false) const; 
      /**
      * @brief Проверка совпадения значений ключевых полей двух объектов
      * @param[in] key_packed Упакованные ключи
      * @param[in] lenkey Размер буфера с упакованными ключами
      * @param[in] buf Буфер с упакованными данными объекта для сравнения
      * @param[in] lenbuf Размер буфера
      * @param[in] key_only Если true, buf содержит только упаковку ключевых данных, иначе весь объект
      * @return true, если значения ключевых полей объектов равны
      */
      static bool keyEqual(const void* key_packed, unsigned lenkey, const void* buf, unsigned lenbuf, bool key_only = false); 
      /**
      * @brief Запрос длины упакованного представления объекта
      * @return длина буфера для упаковки
      */
      unsigned lenPacked() const;
      /**
      * @brief Запрос максимально возможной длины упакованного представления объекта
      * @return максимальная длина буфера для упаковки, 0 - максимальная длина не определена
      */
      static unsigned maxlenPacked();
      /**
      * @brief Запрос длины упакованного представления ключей объекта
      * @return длина буфера для упаковки
      */
      unsigned keylenPacked() const;
      /**
      * @brief Упаковка объекта в буфер
      * @param[in] to_buf Буфер, в который идет упаковка
      * @param[in] lenbuf Размер буфера
      * @return длина упаковки, 0 если буфер мал
      */
      unsigned pack(void* to_buf, unsigned lenbuf) const;
      /**
      * @brief Упаковка только ключей объекта в буфер
      * @param[in] to_buf Буфер, в который идет упаковка
      * @param[in] lenbuf Размер буфера
      * @return длина упаковки, 0 если буфер мал
      */
      unsigned packKey(void* to_buf, unsigned lenbuf) const;
      /**
      * @brief Распаковка объекта из буфера
      * @param[in] from_buf Буфер, содержащий упаковку
      * @param[in] lenbuf Размер буфера
      * @return признак успеха
      */
      bool unpack(const void* from_buf, unsigned lenbuf);
      /**
      * @brief Распаковка ключей объекта из буфера упакованных ключей
      * @param[in] from_buf Буфер, содержащий упаковку
      * @param[in] lenbuf Размер буфера
      * @return признак успеха
      */
      bool unpackKey(const void* from_buf, unsigned lenbuf);
      /**
      * @brief Конструктор по умолчанию
      */
      TGenTcrMsg() {
        m_genTrcNum = 0;
        m_trcState = Message::EUTrcState::EU_TS_NEW;
        m_sensAdd = Message::EUYesNo::EU_NO;
        m_sensDelete = Message::EUYesNo::EU_NO;
        m_imitObj = Message::EUYesNo::EU_NO;
        m_tStart = 0;
        m_tXYUpdate = 0;
        m_tHUpdate = 0;
        m_tHBarUpdate = 0;
        m_tOGPUpdate = 0;
        m_tIndNumUpdate = 0;
        m_x = 0;     
        m_y = 0;     
        m_h = 0;     
        m_hBar = 0;  
        m_Vx = 0;    
        m_Vy = 0;    
        m_psi = 0;   
        m_manevr = Message::EUYesNo::EU_NO;
        m_quant = 0; 
        m_sensCount = 0;
        m_id = 0;    
        m_OGP = Message::EUOGP::EU_OGP_UNKNOW;
        m_objClass = 0;
        m_flyViolatKind = 0;
        memset(m_zones.data(),0,10);
        m_x_progn = 0;
        m_y_progn = 0;
        for (auto &i0 : m_zones_progn) {
          i0 = false;
        }
      }
      /**
      * @brief Явный конструктор
      */
      explicit TGenTcrMsg(
        int32_t              genTrcNum,
        EUTrcState           trcState,
        EUYesNo              sensAdd,
        EUYesNo              sensDelete,
        EUYesNo              imitObj,
        double               tStart,
        double               tXYUpdate,
        double               tHUpdate,
        double               tHBarUpdate,
        double               tOGPUpdate,
        double               tIndNumUpdate,
        float                x,
        float                y,
        float                h,
        float                hBar,
        float                Vx,
        float                Vy,
        float                psi,
        EUYesNo              manevr,
        int16_t              quant,
        int16_t              sensCount,
        uint64_t             id,
        EUOGP                OGP,
        int16_t              objClass,
        int16_t              flyViolatKind,
        ArrZone const &      zones,
        int32_t              x_progn,
        int32_t              y_progn,
        ArrZoneProgn const & zones_progn);
      /**
      * @brief Конструктор копирования
      */
      TGenTcrMsg (TGenTcrMsg const & other);
      /**
      * @brief Конструктор перемещения
      */
      TGenTcrMsg (TGenTcrMsg && other);
      /**
      * @brief Оператор копирования
      */
      TGenTcrMsg& operator = (TGenTcrMsg const & other);
      /**
      * @brief Оператор перемещения
      */
      TGenTcrMsg& operator = (TGenTcrMsg && other);
      /**
      * @brief Оператор сравнения ==
      * @param[in]  other константная ссылка на сравниваемый объект
      * @return  true если параметры одинаковы
      */
      bool operator == (const TGenTcrMsg& other) const;
      /**
      * @brief Оператор сравнения ==
      * @param[in]  other константная ссылка на сравниваемый объект
      * @return  true если параметры не одинаковы
      */
      bool operator != (const TGenTcrMsg& other) const;
      /**
      * @brief Задание значения полю m_genTrcNum
      * @param[in] value Задаваемое значение типа int32_t
      */
      inline void genTrcNum(int32_t value) {
        m_genTrcNum= value;
      }
  
      /**
      * @brief Получение значения поля m_genTrcNum
      * @return Значение поля m_genTrcNum типа int32_t
      */
      inline int32_t genTrcNum() const {
        return m_genTrcNum;
      }
  
      /**
      * @brief Получение ссылки на поле m_genTrcNum
      * @return Ссылка на поле m_genTrcNum типа int32_t
      */
      inline int32_t& genTrcNum() {
        return m_genTrcNum;
      }
  
      /**
      * @brief Задание значения полю m_trcState
      * @param[in] value Задаваемое значение типа EUTrcState
      */
      inline void trcState(EUTrcState value) {
        m_trcState= value;
      }
  
      /**
      * @brief Получение значения поля m_trcState
      * @return Значение поля m_trcState типа EUTrcState
      */
      inline EUTrcState trcState() const {
        return m_trcState;
      }
  
      /**
      * @brief Получение ссылки на поле m_trcState
      * @return Ссылка на поле m_trcState типа EUTrcState
      */
      inline EUTrcState& trcState() {
        return m_trcState;
      }
  
      /**
      * @brief Задание значения полю m_sensAdd
      * @param[in] value Задаваемое значение типа EUYesNo
      */
      inline void sensAdd(EUYesNo value) {
        m_sensAdd= value;
      }
  
      /**
      * @brief Получение значения поля m_sensAdd
      * @return Значение поля m_sensAdd типа EUYesNo
      */
      inline EUYesNo sensAdd() const {
        return m_sensAdd;
      }
  
      /**
      * @brief Получение ссылки на поле m_sensAdd
      * @return Ссылка на поле m_sensAdd типа EUYesNo
      */
      inline EUYesNo& sensAdd() {
        return m_sensAdd;
      }
  
      /**
      * @brief Задание значения полю m_sensDelete
      * @param[in] value Задаваемое значение типа EUYesNo
      */
      inline void sensDelete(EUYesNo value) {
        m_sensDelete= value;
      }
  
      /**
      * @brief Получение значения поля m_sensDelete
      * @return Значение поля m_sensDelete типа EUYesNo
      */
      inline EUYesNo sensDelete() const {
        return m_sensDelete;
      }
  
      /**
      * @brief Получение ссылки на поле m_sensDelete
      * @return Ссылка на поле m_sensDelete типа EUYesNo
      */
      inline EUYesNo& sensDelete() {
        return m_sensDelete;
      }
  
      /**
      * @brief Задание значения полю m_imitObj
      * @param[in] value Задаваемое значение типа EUYesNo
      */
      inline void imitObj(EUYesNo value) {
        m_imitObj= value;
      }
  
      /**
      * @brief Получение значения поля m_imitObj
      * @return Значение поля m_imitObj типа EUYesNo
      */
      inline EUYesNo imitObj() const {
        return m_imitObj;
      }
  
      /**
      * @brief Получение ссылки на поле m_imitObj
      * @return Ссылка на поле m_imitObj типа EUYesNo
      */
      inline EUYesNo& imitObj() {
        return m_imitObj;
      }
  
      /**
      * @brief Задание значения полю m_tStart
      * @param[in] value Задаваемое значение типа double
      */
      inline void tStart(double value) {
        m_tStart= value;
      }
  
      /**
      * @brief Получение значения поля m_tStart
      * @return Значение поля m_tStart типа double
      */
      inline double tStart() const {
        return m_tStart;
      }
  
      /**
      * @brief Получение ссылки на поле m_tStart
      * @return Ссылка на поле m_tStart типа double
      */
      inline double& tStart() {
        return m_tStart;
      }
  
      /**
      * @brief Задание значения полю m_tXYUpdate
      * @param[in] value Задаваемое значение типа double
      */
      inline void tXYUpdate(double value) {
        m_tXYUpdate= value;
      }
  
      /**
      * @brief Получение значения поля m_tXYUpdate
      * @return Значение поля m_tXYUpdate типа double
      */
      inline double tXYUpdate() const {
        return m_tXYUpdate;
      }
  
      /**
      * @brief Получение ссылки на поле m_tXYUpdate
      * @return Ссылка на поле m_tXYUpdate типа double
      */
      inline double& tXYUpdate() {
        return m_tXYUpdate;
      }
  
      /**
      * @brief Задание значения полю m_tHUpdate
      * @param[in] value Задаваемое значение типа double
      */
      inline void tHUpdate(double value) {
        m_tHUpdate= value;
      }
  
      /**
      * @brief Получение значения поля m_tHUpdate
      * @return Значение поля m_tHUpdate типа double
      */
      inline double tHUpdate() const {
        return m_tHUpdate;
      }
  
      /**
      * @brief Получение ссылки на поле m_tHUpdate
      * @return Ссылка на поле m_tHUpdate типа double
      */
      inline double& tHUpdate() {
        return m_tHUpdate;
      }
  
      /**
      * @brief Задание значения полю m_tHBarUpdate
      * @param[in] value Задаваемое значение типа double
      */
      inline void tHBarUpdate(double value) {
        m_tHBarUpdate= value;
      }
  
      /**
      * @brief Получение значения поля m_tHBarUpdate
      * @return Значение поля m_tHBarUpdate типа double
      */
      inline double tHBarUpdate() const {
        return m_tHBarUpdate;
      }
  
      /**
      * @brief Получение ссылки на поле m_tHBarUpdate
      * @return Ссылка на поле m_tHBarUpdate типа double
      */
      inline double& tHBarUpdate() {
        return m_tHBarUpdate;
      }
  
      /**
      * @brief Задание значения полю m_tOGPUpdate
      * @param[in] value Задаваемое значение типа double
      */
      inline void tOGPUpdate(double value) {
        m_tOGPUpdate= value;
      }
  
      /**
      * @brief Получение значения поля m_tOGPUpdate
      * @return Значение поля m_tOGPUpdate типа double
      */
      inline double tOGPUpdate() const {
        return m_tOGPUpdate;
      }
  
      /**
      * @brief Получение ссылки на поле m_tOGPUpdate
      * @return Ссылка на поле m_tOGPUpdate типа double
      */
      inline double& tOGPUpdate() {
        return m_tOGPUpdate;
      }
  
      /**
      * @brief Задание значения полю m_tIndNumUpdate
      * @param[in] value Задаваемое значение типа double
      */
      inline void tIndNumUpdate(double value) {
        m_tIndNumUpdate= value;
      }
  
      /**
      * @brief Получение значения поля m_tIndNumUpdate
      * @return Значение поля m_tIndNumUpdate типа double
      */
      inline double tIndNumUpdate() const {
        return m_tIndNumUpdate;
      }
  
      /**
      * @brief Получение ссылки на поле m_tIndNumUpdate
      * @return Ссылка на поле m_tIndNumUpdate типа double
      */
      inline double& tIndNumUpdate() {
        return m_tIndNumUpdate;
      }
  
      /**
      * @brief Задание значения полю m_x
      * @param[in] value Задаваемое значение типа float
      */
      inline void x(float value) {
        m_x= value;
      }
  
      /**
      * @brief Получение значения поля m_x
      * @return Значение поля m_x типа float
      */
      inline float x() const {
        return m_x;
      }
  
      /**
      * @brief Получение ссылки на поле m_x
      * @return Ссылка на поле m_x типа float
      */
      inline float& x() {
        return m_x;
      }
  
      /**
      * @brief Задание значения полю m_y
      * @param[in] value Задаваемое значение типа float
      */
      inline void y(float value) {
        m_y= value;
      }
  
      /**
      * @brief Получение значения поля m_y
      * @return Значение поля m_y типа float
      */
      inline float y() const {
        return m_y;
      }
  
      /**
      * @brief Получение ссылки на поле m_y
      * @return Ссылка на поле m_y типа float
      */
      inline float& y() {
        return m_y;
      }
  
      /**
      * @brief Задание значения полю m_h
      * @param[in] value Задаваемое значение типа float
      */
      inline void h(float value) {
        m_h= value;
      }
  
      /**
      * @brief Получение значения поля m_h
      * @return Значение поля m_h типа float
      */
      inline float h() const {
        return m_h;
      }
  
      /**
      * @brief Получение ссылки на поле m_h
      * @return Ссылка на поле m_h типа float
      */
      inline float& h() {
        return m_h;
      }
  
      /**
      * @brief Задание значения полю m_hBar
      * @param[in] value Задаваемое значение типа float
      */
      inline void hBar(float value) {
        m_hBar= value;
      }
  
      /**
      * @brief Получение значения поля m_hBar
      * @return Значение поля m_hBar типа float
      */
      inline float hBar() const {
        return m_hBar;
      }
  
      /**
      * @brief Получение ссылки на поле m_hBar
      * @return Ссылка на поле m_hBar типа float
      */
      inline float& hBar() {
        return m_hBar;
      }
  
      /**
      * @brief Задание значения полю m_Vx
      * @param[in] value Задаваемое значение типа float
      */
      inline void Vx(float value) {
        m_Vx= value;
      }
  
      /**
      * @brief Получение значения поля m_Vx
      * @return Значение поля m_Vx типа float
      */
      inline float Vx() const {
        return m_Vx;
      }
  
      /**
      * @brief Получение ссылки на поле m_Vx
      * @return Ссылка на поле m_Vx типа float
      */
      inline float& Vx() {
        return m_Vx;
      }
  
      /**
      * @brief Задание значения полю m_Vy
      * @param[in] value Задаваемое значение типа float
      */
      inline void Vy(float value) {
        m_Vy= value;
      }
  
      /**
      * @brief Получение значения поля m_Vy
      * @return Значение поля m_Vy типа float
      */
      inline float Vy() const {
        return m_Vy;
      }
  
      /**
      * @brief Получение ссылки на поле m_Vy
      * @return Ссылка на поле m_Vy типа float
      */
      inline float& Vy() {
        return m_Vy;
      }
  
      /**
      * @brief Задание значения полю m_psi
      * @param[in] value Задаваемое значение типа float
      */
      inline void psi(float value) {
        m_psi= value;
      }
  
      /**
      * @brief Получение значения поля m_psi
      * @return Значение поля m_psi типа float
      */
      inline float psi() const {
        return m_psi;
      }
  
      /**
      * @brief Получение ссылки на поле m_psi
      * @return Ссылка на поле m_psi типа float
      */
      inline float& psi() {
        return m_psi;
      }
  
      /**
      * @brief Задание значения полю m_manevr
      * @param[in] value Задаваемое значение типа EUYesNo
      */
      inline void manevr(EUYesNo value) {
        m_manevr= value;
      }
  
      /**
      * @brief Получение значения поля m_manevr
      * @return Значение поля m_manevr типа EUYesNo
      */
      inline EUYesNo manevr() const {
        return m_manevr;
      }
  
      /**
      * @brief Получение ссылки на поле m_manevr
      * @return Ссылка на поле m_manevr типа EUYesNo
      */
      inline EUYesNo& manevr() {
        return m_manevr;
      }
  
      /**
      * @brief Задание значения полю m_quant
      * @param[in] value Задаваемое значение типа int16_t
      */
      inline void quant(int16_t value) {
        m_quant= value;
      }
  
      /**
      * @brief Получение значения поля m_quant
      * @return Значение поля m_quant типа int16_t
      */
      inline int16_t quant() const {
        return m_quant;
      }
  
      /**
      * @brief Получение ссылки на поле m_quant
      * @return Ссылка на поле m_quant типа int16_t
      */
      inline int16_t& quant() {
        return m_quant;
      }
  
      /**
      * @brief Задание значения полю m_sensCount
      * @param[in] value Задаваемое значение типа int16_t
      */
      inline void sensCount(int16_t value) {
        m_sensCount= value;
      }
  
      /**
      * @brief Получение значения поля m_sensCount
      * @return Значение поля m_sensCount типа int16_t
      */
      inline int16_t sensCount() const {
        return m_sensCount;
      }
  
      /**
      * @brief Получение ссылки на поле m_sensCount
      * @return Ссылка на поле m_sensCount типа int16_t
      */
      inline int16_t& sensCount() {
        return m_sensCount;
      }
  
      /**
      * @brief Задание значения полю m_id
      * @param[in] value Задаваемое значение типа uint64_t
      */
      inline void id(uint64_t value) {
        m_id= value;
      }
  
      /**
      * @brief Получение значения поля m_id
      * @return Значение поля m_id типа uint64_t
      */
      inline uint64_t id() const {
        return m_id;
      }
  
      /**
      * @brief Получение ссылки на поле m_id
      * @return Ссылка на поле m_id типа uint64_t
      */
      inline uint64_t& id() {
        return m_id;
      }
  
      /**
      * @brief Задание значения полю m_OGP
      * @param[in] value Задаваемое значение типа EUOGP
      */
      inline void OGP(EUOGP value) {
        m_OGP= value;
      }
  
      /**
      * @brief Получение значения поля m_OGP
      * @return Значение поля m_OGP типа EUOGP
      */
      inline EUOGP OGP() const {
        return m_OGP;
      }
  
      /**
      * @brief Получение ссылки на поле m_OGP
      * @return Ссылка на поле m_OGP типа EUOGP
      */
      inline EUOGP& OGP() {
        return m_OGP;
      }
  
      /**
      * @brief Задание значения полю m_objClass
      * @param[in] value Задаваемое значение типа int16_t
      */
      inline void objClass(int16_t value) {
        m_objClass= value;
      }
  
      /**
      * @brief Получение значения поля m_objClass
      * @return Значение поля m_objClass типа int16_t
      */
      inline int16_t objClass() const {
        return m_objClass;
      }
  
      /**
      * @brief Получение ссылки на поле m_objClass
      * @return Ссылка на поле m_objClass типа int16_t
      */
      inline int16_t& objClass() {
        return m_objClass;
      }
  
      /**
      * @brief Задание значения полю m_flyViolatKind
      * @param[in] value Задаваемое значение типа int16_t
      */
      inline void flyViolatKind(int16_t value) {
        m_flyViolatKind= value;
      }
  
      /**
      * @brief Получение значения поля m_flyViolatKind
      * @return Значение поля m_flyViolatKind типа int16_t
      */
      inline int16_t flyViolatKind() const {
        return m_flyViolatKind;
      }
  
      /**
      * @brief Получение ссылки на поле m_flyViolatKind
      * @return Ссылка на поле m_flyViolatKind типа int16_t
      */
      inline int16_t& flyViolatKind() {
        return m_flyViolatKind;
      }
  
      /**
      * @brief Копирование данных объекта value в поле m_zones
      * @param[in] value Объект копирования типа ArrZone
      */
      inline void zones(ArrZone const& value) {
        m_zones= value;
      }
  
      /**
      * @brief Перемещение данных объекта value в поле m_zones
      * @param[in] value Объект перемещения типа ArrZone
      */
      inline void zones(ArrZone && value) {
        m_zones= std::move(value);
      }
  
      /**
      * @brief Получение константной ссылки на поле m_zones
      * @return Константная ссылка на поле m_zones типа ArrZone
      */
      inline const ArrZone& zones() const {
        return m_zones;
      }
  
      /**
      * @brief Получение ссылки на поле m_zones
      * @return Ссылка на поле m_zones типа ArrZone
      */
      inline ArrZone& zones() {
        return m_zones;
      }
  
      /**
      * @brief Задание значения полю m_x_progn
      * @param[in] value Задаваемое значение типа int32_t
      */
      inline void x_progn(int32_t value) {
        m_x_progn= value;
      }
  
      /**
      * @brief Получение значения поля m_x_progn
      * @return Значение поля m_x_progn типа int32_t
      */
      inline int32_t x_progn() const {
        return m_x_progn;
      }
  
      /**
      * @brief Получение ссылки на поле m_x_progn
      * @return Ссылка на поле m_x_progn типа int32_t
      */
      inline int32_t& x_progn() {
        return m_x_progn;
      }
  
      /**
      * @brief Задание значения полю m_y_progn
      * @param[in] value Задаваемое значение типа int32_t
      */
      inline void y_progn(int32_t value) {
        m_y_progn= value;
      }
  
      /**
      * @brief Получение значения поля m_y_progn
      * @return Значение поля m_y_progn типа int32_t
      */
      inline int32_t y_progn() const {
        return m_y_progn;
      }
  
      /**
      * @brief Получение ссылки на поле m_y_progn
      * @return Ссылка на поле m_y_progn типа int32_t
      */
      inline int32_t& y_progn() {
        return m_y_progn;
      }
  
      /**
      * @brief Копирование данных объекта value в поле m_zones_progn
      * @param[in] value Объект копирования типа ArrZoneProgn
      */
      inline void zones_progn(ArrZoneProgn const& value) {
        m_zones_progn= value;
      }
  
      /**
      * @brief Перемещение данных объекта value в поле m_zones_progn
      * @param[in] value Объект перемещения типа ArrZoneProgn
      */
      inline void zones_progn(ArrZoneProgn && value) {
        m_zones_progn= std::move(value);
      }
  
      /**
      * @brief Получение константной ссылки на поле m_zones_progn
      * @return Константная ссылка на поле m_zones_progn типа ArrZoneProgn
      */
      inline const ArrZoneProgn& zones_progn() const {
        return m_zones_progn;
      }
  
      /**
      * @brief Получение ссылки на поле m_zones_progn
      * @return Ссылка на поле m_zones_progn типа ArrZoneProgn
      */
      inline ArrZoneProgn& zones_progn() {
        return m_zones_progn;
      }
  
      /**
      * @name Атрибуты класса
      * @{
      */
      int32_t      m_genTrcNum;     /**< Номер обобщенной трассы */
      EUTrcState   m_trcState;      /**< Признак состояния сопровождения трассы */
      EUYesNo      m_sensAdd;       /**< Добавление источника */
      EUYesNo      m_sensDelete;    /**< Удаление источника */
      EUYesNo      m_imitObj;       /**< Признак имитационного объекта */
      double       m_tStart;        /**< Время образования обобщ. трассы */
      double       m_tXYUpdate;     /**< Время обновления координат Х и У */
      double       m_tHUpdate;      /**< Время обновления высоты */
      double       m_tHBarUpdate;   /**< Время обновления барометрической высоты */
      double       m_tOGPUpdate;    /**< Время обновления ОГП */
      double       m_tIndNumUpdate; /**< Время обновления индивидуального номера */
      float        m_x;             /**< Координата Х */
      float        m_y;             /**< Координата У */
      float        m_h;             /**< Высота (глубина) */
      float        m_hBar;          /**< Барометрическая высота */
      float        m_Vx;            /**< Составляющая скорости по Х */
      float        m_Vy;            /**< Составляющая скорости по У */
      float        m_psi;           /**< Курс движения */
      EUYesNo      m_manevr;        /**< Признак наличия маневра */
      int16_t      m_quant;         /**< Количественный состав (1 - 15) */
      int16_t      m_sensCount;     /**< Кол-во источников сопровождающих данную трассу */
      uint64_t     m_id;
      EUOGP        m_OGP;           /**< ОГП */
      int16_t      m_objClass;      /**< Категория объекта: возд, на повр-ти */
      int16_t      m_flyViolatKind; /**< Вид нарушения режима полета */
      ArrZone      m_zones;         /**< Принадлежность объекта зоне */
      int32_t      m_x_progn;       /**< Прогноз координаты Х */
      int32_t      m_y_progn;       /**< Прогноз координаты Y */
      ArrZoneProgn m_zones_progn;   /**< Принадлежность объекта зоне */
      /**
      * @}
      */
  };
  

} // close namespace Message
#include "Message_DCPS_Pack.h"
#endif
