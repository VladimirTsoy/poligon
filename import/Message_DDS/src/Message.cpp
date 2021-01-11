/******************************************************
 * Файл сгенирирован XML_DSS компилятором
 * Назначение: Определение методов пользовательских типов, заданного модуля
 * Имя файла:  /home/user/qt/Poligon/POLIGON02/../import/Message_DDS/src/Message.cpp
 * Имя XML-файла (источник): /home/user/qt/Poligon/POLIGON02/RDDS_TGenMsg/import/xml/Message.xml
 * Дата создания: 28.12.20 04:15:01 UTC
 * РСРД 0.1
 * Copyright (c) ОАО "НПО РусБИТех"
 ******************************************************/
#include "Message.h"
namespace Message {
  const char* command_str::nameOfType = "Message::command_str";
  
  command_str::command_str(const void* from_buf, unsigned lenbuf, bool key_only) {
    if (key_only) {
      unpackKey(from_buf, lenbuf);
    } else {
      unpack(from_buf, lenbuf);
    }
  }
  const char* TGenTcrMsg::nameOfType = "Message::TGenTcrMsg";
  
  TGenTcrMsg::TGenTcrMsg(const void* from_buf, unsigned lenbuf, bool key_only) {
    if (key_only) {
      unpackKey(from_buf, lenbuf);
    } else {
      unpack(from_buf, lenbuf);
    }
  }
  TGenTcrMsg::TGenTcrMsg(
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
    ArrZoneProgn const & zones_progn) :
      m_genTrcNum    (genTrcNum),
      m_trcState     (trcState),
      m_sensAdd      (sensAdd),
      m_sensDelete   (sensDelete),
      m_imitObj      (imitObj),
      m_tStart       (tStart),
      m_tXYUpdate    (tXYUpdate),
      m_tHUpdate     (tHUpdate),
      m_tHBarUpdate  (tHBarUpdate),
      m_tOGPUpdate   (tOGPUpdate),
      m_tIndNumUpdate(tIndNumUpdate),
      m_x            (x),
      m_y            (y),
      m_h            (h),
      m_hBar         (hBar),
      m_Vx           (Vx),
      m_Vy           (Vy),
      m_psi          (psi),
      m_manevr       (manevr),
      m_quant        (quant),
      m_sensCount    (sensCount),
      m_id           (id),
      m_OGP          (OGP),
      m_objClass     (objClass),
      m_flyViolatKind(flyViolatKind),
      m_zones        (zones),
      m_x_progn      (x_progn),
      m_y_progn      (y_progn),
      m_zones_progn  (zones_progn) {}
  
  TGenTcrMsg::TGenTcrMsg(TGenTcrMsg const & other) {
    m_genTrcNum     = other.m_genTrcNum;
    m_trcState      = other.m_trcState;
    m_sensAdd       = other.m_sensAdd;
    m_sensDelete    = other.m_sensDelete;
    m_imitObj       = other.m_imitObj;
    m_tStart        = other.m_tStart;
    m_tXYUpdate     = other.m_tXYUpdate;
    m_tHUpdate      = other.m_tHUpdate;
    m_tHBarUpdate   = other.m_tHBarUpdate;
    m_tOGPUpdate    = other.m_tOGPUpdate;
    m_tIndNumUpdate = other.m_tIndNumUpdate;
    m_x             = other.m_x;
    m_y             = other.m_y;
    m_h             = other.m_h;
    m_hBar          = other.m_hBar;
    m_Vx            = other.m_Vx;
    m_Vy            = other.m_Vy;
    m_psi           = other.m_psi;
    m_manevr        = other.m_manevr;
    m_quant         = other.m_quant;
    m_sensCount     = other.m_sensCount;
    m_id            = other.m_id;
    m_OGP           = other.m_OGP;
    m_objClass      = other.m_objClass;
    m_flyViolatKind = other.m_flyViolatKind;
    m_zones         = other.m_zones;
    m_x_progn       = other.m_x_progn;
    m_y_progn       = other.m_y_progn;
    m_zones_progn   = other.m_zones_progn;
  }
  TGenTcrMsg::TGenTcrMsg(TGenTcrMsg && other) {
    m_genTrcNum     = std::move(other.m_genTrcNum);
    m_trcState      = std::move(other.m_trcState);
    m_sensAdd       = std::move(other.m_sensAdd);
    m_sensDelete    = std::move(other.m_sensDelete);
    m_imitObj       = std::move(other.m_imitObj);
    m_tStart        = std::move(other.m_tStart);
    m_tXYUpdate     = std::move(other.m_tXYUpdate);
    m_tHUpdate      = std::move(other.m_tHUpdate);
    m_tHBarUpdate   = std::move(other.m_tHBarUpdate);
    m_tOGPUpdate    = std::move(other.m_tOGPUpdate);
    m_tIndNumUpdate = std::move(other.m_tIndNumUpdate);
    m_x             = std::move(other.m_x);
    m_y             = std::move(other.m_y);
    m_h             = std::move(other.m_h);
    m_hBar          = std::move(other.m_hBar);
    m_Vx            = std::move(other.m_Vx);
    m_Vy            = std::move(other.m_Vy);
    m_psi           = std::move(other.m_psi);
    m_manevr        = std::move(other.m_manevr);
    m_quant         = std::move(other.m_quant);
    m_sensCount     = std::move(other.m_sensCount);
    m_id            = std::move(other.m_id);
    m_OGP           = std::move(other.m_OGP);
    m_objClass      = std::move(other.m_objClass);
    m_flyViolatKind = std::move(other.m_flyViolatKind);
    m_zones         = std::move(other.m_zones);
    m_x_progn       = std::move(other.m_x_progn);
    m_y_progn       = std::move(other.m_y_progn);
    m_zones_progn   = std::move(other.m_zones_progn);
  }
  TGenTcrMsg& TGenTcrMsg::operator =(TGenTcrMsg const & other) {
    if (this != &other) {
      m_genTrcNum     = other.m_genTrcNum;
      m_trcState      = other.m_trcState;
      m_sensAdd       = other.m_sensAdd;
      m_sensDelete    = other.m_sensDelete;
      m_imitObj       = other.m_imitObj;
      m_tStart        = other.m_tStart;
      m_tXYUpdate     = other.m_tXYUpdate;
      m_tHUpdate      = other.m_tHUpdate;
      m_tHBarUpdate   = other.m_tHBarUpdate;
      m_tOGPUpdate    = other.m_tOGPUpdate;
      m_tIndNumUpdate = other.m_tIndNumUpdate;
      m_x             = other.m_x;
      m_y             = other.m_y;
      m_h             = other.m_h;
      m_hBar          = other.m_hBar;
      m_Vx            = other.m_Vx;
      m_Vy            = other.m_Vy;
      m_psi           = other.m_psi;
      m_manevr        = other.m_manevr;
      m_quant         = other.m_quant;
      m_sensCount     = other.m_sensCount;
      m_id            = other.m_id;
      m_OGP           = other.m_OGP;
      m_objClass      = other.m_objClass;
      m_flyViolatKind = other.m_flyViolatKind;
      m_zones         = other.m_zones;
      m_x_progn       = other.m_x_progn;
      m_y_progn       = other.m_y_progn;
      m_zones_progn   = other.m_zones_progn;
    }
    return *this;
  }
  TGenTcrMsg& TGenTcrMsg::operator = (TGenTcrMsg && other) {
    if (this != &other) {
      m_genTrcNum     = std::move(other.m_genTrcNum);
      m_trcState      = std::move(other.m_trcState);
      m_sensAdd       = std::move(other.m_sensAdd);
      m_sensDelete    = std::move(other.m_sensDelete);
      m_imitObj       = std::move(other.m_imitObj);
      m_tStart        = std::move(other.m_tStart);
      m_tXYUpdate     = std::move(other.m_tXYUpdate);
      m_tHUpdate      = std::move(other.m_tHUpdate);
      m_tHBarUpdate   = std::move(other.m_tHBarUpdate);
      m_tOGPUpdate    = std::move(other.m_tOGPUpdate);
      m_tIndNumUpdate = std::move(other.m_tIndNumUpdate);
      m_x             = std::move(other.m_x);
      m_y             = std::move(other.m_y);
      m_h             = std::move(other.m_h);
      m_hBar          = std::move(other.m_hBar);
      m_Vx            = std::move(other.m_Vx);
      m_Vy            = std::move(other.m_Vy);
      m_psi           = std::move(other.m_psi);
      m_manevr        = std::move(other.m_manevr);
      m_quant         = std::move(other.m_quant);
      m_sensCount     = std::move(other.m_sensCount);
      m_id            = std::move(other.m_id);
      m_OGP           = std::move(other.m_OGP);
      m_objClass      = std::move(other.m_objClass);
      m_flyViolatKind = std::move(other.m_flyViolatKind);
      m_zones         = std::move(other.m_zones);
      m_x_progn       = std::move(other.m_x_progn);
      m_y_progn       = std::move(other.m_y_progn);
      m_zones_progn   = std::move(other.m_zones_progn);
    }
    return *this;
  }
  bool TGenTcrMsg::operator == (const TGenTcrMsg& other) const {
    if (this != &other) {
      return
        m_genTrcNum     == other.m_genTrcNum &&
        m_trcState      == other.m_trcState &&
        m_sensAdd       == other.m_sensAdd &&
        m_sensDelete    == other.m_sensDelete &&
        m_imitObj       == other.m_imitObj &&
        m_tStart        == other.m_tStart &&
        m_tXYUpdate     == other.m_tXYUpdate &&
        m_tHUpdate      == other.m_tHUpdate &&
        m_tHBarUpdate   == other.m_tHBarUpdate &&
        m_tOGPUpdate    == other.m_tOGPUpdate &&
        m_tIndNumUpdate == other.m_tIndNumUpdate &&
        m_x             == other.m_x &&
        m_y             == other.m_y &&
        m_h             == other.m_h &&
        m_hBar          == other.m_hBar &&
        m_Vx            == other.m_Vx &&
        m_Vy            == other.m_Vy &&
        m_psi           == other.m_psi &&
        m_manevr        == other.m_manevr &&
        m_quant         == other.m_quant &&
        m_sensCount     == other.m_sensCount &&
        m_id            == other.m_id &&
        m_OGP           == other.m_OGP &&
        m_objClass      == other.m_objClass &&
        m_flyViolatKind == other.m_flyViolatKind &&
        m_zones         == other.m_zones &&
        m_x_progn       == other.m_x_progn &&
        m_y_progn       == other.m_y_progn &&
        m_zones_progn   == other.m_zones_progn;
    }
    return true;
  }
  
  bool TGenTcrMsg::operator != (const TGenTcrMsg& other) const {
    return !(*this == other);
  }
  
  

} // close namespace Message
