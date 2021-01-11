/******************************************************
 * Файл сгенирирован XML_DSS компилятором
 * Назначение: Определение функций и методов распаковки и упаковки данных пользователя
 * Имя файла:  /home/user/qt/Poligon/POLIGON02/../import/Message_DDS/src/Message_DCPS_Pack.cpp
 * Имя XML-файла (источник): /home/user/qt/Poligon/POLIGON02/RDDS_TGenMsg/import/xml/Message.xml
 * Дата создания: 28.12.20 04:15:01 UTC
 * РСРД 0.1
 * Copyright (c) ОАО "НПО РусБИТех"
 ******************************************************/
#include "Message_DCPS_Pack.h"
#include "rdds_pack.h"
namespace Message  {
  unsigned command_str::pack(void* to_buf, unsigned in_lenbuf) const {
    unsigned lenbuf = in_lenbuf - 4;
    if (lenbuf<4) return 0;
    memcpy(to_buf,(void*)&RDDS_PACK::ex_CDR_HEADER_LE,4);
    uint8_t* ptrDist = (uint8_t*)to_buf+4;
    memcpy(ptrDist, &m_command,4);
    return 8;
  }
  bool command_str::unpack(const void* in_from_buf, unsigned in_lenbuf) {
    if (in_lenbuf < 8) {return false;}
    RDDS_PACK::CDR_HEADER cdrHEADER;
    RDDS_PACK::unpack(cdrHEADER,in_from_buf,in_lenbuf);
    uint8_t* ptrSrc = (uint8_t*)in_from_buf+4;
    if (cdrHEADER.Encapsulation == RDDS_PACK::EnEncapsulation::CDR_LE) {
      memcpy(&m_command,ptrSrc,4); 
    } else {
      memcpy(&m_command,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_command);
    }
    return true;
  }
  unsigned command_str::lenPacked() const {
    return (unsigned)8;
  }
  unsigned command_str::maxlenPacked() {
    return (unsigned)8;
  }
  unsigned TGenTcrMsg::pack(void* to_buf, unsigned in_lenbuf) const {
    unsigned lenbuf = in_lenbuf - 4;
    if (lenbuf<145) return 0;
    memcpy(to_buf,(void*)&RDDS_PACK::ex_CDR_HEADER_LE,4);
    uint8_t* ptrDist = (uint8_t*)to_buf+4;
    memcpy(ptrDist, &m_genTrcNum,4);
    memcpy(ptrDist +4,&m_trcState,2);
    memcpy(ptrDist +6,&m_sensAdd,2);
    memcpy(ptrDist +8,&m_sensDelete,2);
    memcpy(ptrDist +10,&m_imitObj,2);
    memcpy(ptrDist +16,&m_tStart,8);
    memcpy(ptrDist +24,&m_tXYUpdate,8);
    memcpy(ptrDist +32,&m_tHUpdate,8);
    memcpy(ptrDist +40,&m_tHBarUpdate,8);
    memcpy(ptrDist +48,&m_tOGPUpdate,8);
    memcpy(ptrDist +56,&m_tIndNumUpdate,8);
    memcpy(ptrDist +64,&m_x,4);
    memcpy(ptrDist +68,&m_y,4);
    memcpy(ptrDist +72,&m_h,4);
    memcpy(ptrDist +76,&m_hBar,4);
    memcpy(ptrDist +80,&m_Vx,4);
    memcpy(ptrDist +84,&m_Vy,4);
    memcpy(ptrDist +88,&m_psi,4);
    memcpy(ptrDist +92,&m_manevr,2);
    memcpy(ptrDist +94,&m_quant,2);
    memcpy(ptrDist +96,&m_sensCount,2);
    memcpy(ptrDist +104,&m_id,8);
    memcpy(ptrDist +112,&m_OGP,4);
    memcpy(ptrDist +116,&m_objClass,2);
    memcpy(ptrDist +118,&m_flyViolatKind,2);
    memcpy(ptrDist +120,&m_zones,10);
    memcpy(ptrDist +132,&m_x_progn,4);
    memcpy(ptrDist +136,&m_y_progn,4);
    memcpy(ptrDist +140,&m_zones_progn,5);
    return 149;
  }
  unsigned next(Message::ArrZone& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf){
    unsigned sizeOfArray = 10;
    uint32_t shift = pos%2;
    pos = pos + shift + sizeOfArray;
    if (pos > lenbuf) {return 0;}
    return pos;
  }
  unsigned nextCH(Message::ArrZone& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf){
    unsigned sizeOfArray = 10;
    uint32_t shift = pos%2;
    pos = pos + shift + sizeOfArray;
    if (pos > lenbuf) {return 0;}
    return pos;
  }
  unsigned next(Message::ArrZoneProgn& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf){
    unsigned sizeOfArray = 5;
    uint32_t shift = 0;
    pos = pos + shift + sizeOfArray;
    if (pos > lenbuf) {return 0;}
    return pos;
  }
  unsigned nextCH(Message::ArrZoneProgn& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf){
    unsigned sizeOfArray = 5;
    uint32_t shift = 0;
    pos = pos + shift + sizeOfArray;
    if (pos > lenbuf) {return 0;}
    return pos;
  }
  bool TGenTcrMsg::unpack(const void* in_from_buf, unsigned in_lenbuf) {
    if (in_lenbuf < 149) {return false;}
    RDDS_PACK::CDR_HEADER cdrHEADER;
    RDDS_PACK::unpack(cdrHEADER,in_from_buf,in_lenbuf);
    uint8_t* ptrSrc = (uint8_t*)in_from_buf+4;
    if (cdrHEADER.Encapsulation == RDDS_PACK::EnEncapsulation::CDR_LE) {
      memcpy(&m_genTrcNum,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_trcState,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_sensAdd,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_sensDelete,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_imitObj,ptrSrc,2); 
      ptrSrc += 6;
      memcpy(&m_tStart,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_tXYUpdate,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_tHUpdate,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_tHBarUpdate,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_tOGPUpdate,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_tIndNumUpdate,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_x,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_y,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_h,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_hBar,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_Vx,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_Vy,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_psi,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_manevr,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_quant,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_sensCount,ptrSrc,2); 
      ptrSrc += 8;
      memcpy(&m_id,ptrSrc,8); 
      ptrSrc += 8;
      memcpy(&m_OGP,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_objClass,ptrSrc,2); 
      ptrSrc += 2;
      memcpy(&m_flyViolatKind,ptrSrc,2); 
      ptrSrc += 2;
      {
        auto src = m_zones.data();
        memcpy(src,ptrSrc,10);
        ptrSrc += 8;
      }
      ptrSrc += 4;
      memcpy(&m_x_progn,ptrSrc,4); 
      ptrSrc += 4;
      memcpy(&m_y_progn,ptrSrc,4); 
      ptrSrc += 4;
      {
        auto src = m_zones_progn.data();
        memcpy(src,ptrSrc,5);
        ptrSrc += 4;
      }
    } else {
      ptrSrc += 3;
      memcpy(&m_genTrcNum,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_genTrcNum);
      ptrSrc += 4;
      memcpy(&m_trcState,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_trcState);
      ptrSrc += 2;
      memcpy(&m_sensAdd,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_sensAdd);
      ptrSrc += 2;
      memcpy(&m_sensDelete,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_sensDelete);
      ptrSrc += 2;
      memcpy(&m_imitObj,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_imitObj);
      ptrSrc += 2;
      memcpy(&m_tStart,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tStart);
      ptrSrc += 8;
      memcpy(&m_tXYUpdate,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tXYUpdate);
      ptrSrc += 8;
      memcpy(&m_tHUpdate,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tHUpdate);
      ptrSrc += 8;
      memcpy(&m_tHBarUpdate,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tHBarUpdate);
      ptrSrc += 8;
      memcpy(&m_tOGPUpdate,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tOGPUpdate);
      ptrSrc += 8;
      memcpy(&m_tIndNumUpdate,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_tIndNumUpdate);
      ptrSrc += 8;
      memcpy(&m_x,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_x);
      ptrSrc += 4;
      memcpy(&m_y,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_y);
      ptrSrc += 4;
      memcpy(&m_h,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_h);
      ptrSrc += 4;
      memcpy(&m_hBar,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_hBar);
      ptrSrc += 4;
      memcpy(&m_Vx,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_Vx);
      ptrSrc += 4;
      memcpy(&m_Vy,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_Vy);
      ptrSrc += 4;
      memcpy(&m_psi,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_psi);
      ptrSrc += 4;
      memcpy(&m_manevr,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_manevr);
      ptrSrc += 2;
      memcpy(&m_quant,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_quant);
      ptrSrc += 2;
      memcpy(&m_sensCount,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_sensCount);
      ptrSrc += 8;
      memcpy(&m_id,ptrSrc,8); 
      RDDS_PACK::changeENDIAN(m_id);
      ptrSrc += 8;
      memcpy(&m_OGP,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_OGP);
      ptrSrc += 4;
      memcpy(&m_objClass,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_objClass);
      ptrSrc += 2;
      memcpy(&m_flyViolatKind,ptrSrc,2); 
      RDDS_PACK::changeENDIAN(m_flyViolatKind);
      ptrSrc += 2;
      {
        auto src = m_zones.data();
        for (unsigned i=0; i<5; i++) {
          src = src + i;
          memcpy(src,ptrSrc,2);
          RDDS_PACK::changeENDIAN(src,2);
          if (i != 4) {
            ptrSrc = ptrSrc + 2;
          }
        }
      }
      ptrSrc += 4;
      memcpy(&m_x_progn,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_x_progn);
      ptrSrc += 4;
      memcpy(&m_y_progn,ptrSrc,4); 
      RDDS_PACK::changeENDIAN(m_y_progn);
      ptrSrc += 4;
      {
        auto src = m_zones_progn.data();
        memcpy(src,ptrSrc,5);
        ptrSrc += 4;
      }
    }
    return true;
  }
  unsigned TGenTcrMsg::lenPacked() const {
    return (unsigned)149;
  }
  unsigned TGenTcrMsg::maxlenPacked() {
    return (unsigned)149;
  }
  r_dds::dds::KeyHash_t TGenTcrMsg::keyHash() const{
    r_dds::dds::KeyHash_t Hash;
    memset(Hash.hash,0,16);
    memcpy(Hash.hash,&m_id,8);
    RDDS_PACK::changeENDIAN(Hash.hash,8);
    memcpy(Hash.hash+8,&m_genTrcNum,4);
    RDDS_PACK::changeENDIAN(Hash.hash+8,4);
    return Hash;
  }
  bool TGenTcrMsg::keyEqual(const Message::TGenTcrMsg& object) const {
    if (object.m_id!=m_id) return false;
    if (object.m_genTrcNum!=m_genTrcNum) return false;
    return true;
  }
  bool TGenTcrMsg::keyEqual(const void* from_buf, unsigned lenbuf, bool key_only) const {
    bool isOK=true;
    if (key_only) {
      RDDS_PACK::CDR_HEADER cdrHEADER;
      RDDS_PACK::unpack(cdrHEADER,from_buf,lenbuf);
      uint8_t* ptrSrc = (uint8_t*)from_buf+4;
      unsigned pos = 0;
      if (lenbuf < 16) return false;
      if (cdrHEADER.Encapsulation == RDDS_PACK::EnEncapsulation::CDR_LE) {
        if (memcmp(ptrSrc, &m_id, 8) !=0) return false;
        if (memcmp(ptrSrc+8, &m_genTrcNum, 4) !=0) return false;
      } else {
        if (!RDDS_PACK::comparePrimitiveCH(m_id,(void*)ptrSrc,pos,lenbuf-4)) return false;
        if (!RDDS_PACK::comparePrimitiveCH(m_genTrcNum,(void*)ptrSrc,pos,lenbuf-4)) return false;
      }
    } else {
      TGenTcrMsg tmp;
      tmp.unpack(from_buf,lenbuf);
      return keyEqual(tmp);
    };
    return isOK;
  }
  unsigned TGenTcrMsg::packKey(void* to_buf, unsigned lenbuf) const {
    if (lenbuf<16) return 0;
    memcpy(to_buf,(void*)&RDDS_PACK::ex_CDR_HEADER_LE,4);
    uint8_t* ptrDist = (uint8_t*)to_buf+4;
    memcpy(ptrDist, &m_id,8);
    memcpy(ptrDist +8,&m_genTrcNum,4);
    return 16;
  }
  unsigned TGenTcrMsg::keylenPacked() const { 
    return 16;
  }
  bool TGenTcrMsg::unpackKey(const void* from_buf, unsigned lenbuf) {
    bool isOK=true;
    if (lenbuf < 16) return false;
    RDDS_PACK::CDR_HEADER cdrHEADER;
    RDDS_PACK::unpack(cdrHEADER,from_buf,lenbuf);
    uint8_t* ptrSrc = (uint8_t*)from_buf+4;
    unsigned pos=0;
    if (cdrHEADER.Encapsulation == RDDS_PACK::EnEncapsulation::CDR_LE) {
        memcpy(&m_id, ptrSrc,8);
        memcpy(&m_genTrcNum, ptrSrc+8,4);
    } else {
        pos = RDDS_PACK::unpackPrimitiveCH(m_id,ptrSrc,pos,lenbuf-4);
        if (pos == 0) return false;
        pos = RDDS_PACK::unpackPrimitiveCH(m_genTrcNum,ptrSrc,pos,lenbuf-4);
        if (pos == 0) return false;
    }
    return isOK;
  }
  bool TGenTcrMsg::keyEqual(const void* key_packed, unsigned lenkey, const void* buf, unsigned lenbuf, bool key_only) { 
    TGenTcrMsg tmp1;
    bool isEquel;
    if (!tmp1.unpackKey(key_packed,lenkey)) return false;
    isEquel = tmp1.keyEqual(buf,lenbuf,key_only);
    return isEquel;
  }
} // close namespace Message
