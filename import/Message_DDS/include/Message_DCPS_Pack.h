/******************************************************
 * Файл сгенирирован XML_DSS компилятором
 * Назначение: Описание функций и методов распаковки и упаковки данных пользователя
 * Имя файла:  /home/user/qt/Poligon/POLIGON02/../import/Message_DDS/include/Message_DCPS_Pack.h
 * Имя XML-файла (источник): /home/user/qt/Poligon/POLIGON02/RDDS_TGenMsg/import/xml/Message.xml
 * Дата создания: 28.12.20 04:15:01 UTC
 * РСРД 0.1
 * Copyright (c) ОАО "НПО РусБИТех"
 ******************************************************/
#ifndef RBT_MESSAGE_DCPS_PACK_H
#define RBT_MESSAGE_DCPS_PACK_H
#include "Message.h"
namespace Message {
  unsigned next(Message::ArrZone& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf);
  unsigned nextCH(Message::ArrZone& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf);
  unsigned next(Message::ArrZoneProgn& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf);
  unsigned nextCH(Message::ArrZoneProgn& ArrayObj, const void* from_buf, unsigned pos, unsigned lenbuf);
} // close namespace Message
#endif
