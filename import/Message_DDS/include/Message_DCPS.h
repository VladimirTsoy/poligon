/******************************************************
 * Файл сгенирирован XML_DSS компилятором
 * Назначение: Реализация всех стандартных методов DDS для топиков в данном модуле
 * Имя файла:  /home/user/qt/Poligon/POLIGON02/../import/Message_DDS/include/Message_DCPS.h
 * Имя XML-файла (источник): /home/user/qt/Poligon/POLIGON02/RDDS_TGenMsg/import/xml/Message.xml
 * Дата создания: 28.12.20 04:15:01 UTC
 * РСРД 0.1
 * Copyright (c) ОАО "НПО РусБИТех"
 ******************************************************/
#ifndef RBT_MESSAGE_DCPS_H
#define RBT_MESSAGE_DCPS_H
#include <r_dds/DataReaderTemplate.h>
#include <r_dds/DataWriterTemplate.h>
#include <r_dds/TypeSupportTemplate.h>
#include "Message.h"

namespace Message {
  typedef r_dds::dcps::api::DataReaderTemplate< ::Message::command_str > command_strDataReader;
  typedef r_dds::dcps::api::DataWriterTemplate< ::Message::command_str > command_strDataWriter;

  typedef r_dds::dcps::api::TypeSupportFactoryTemplate<
    ::Message::command_str, 
    ::Message::command_strDataWriter, ::Message::command_strDataReader >  command_strTypeSupportFactory;

  typedef r_dds::dcps::api::TypeSupportTemplate< ::Message::command_str, command_strTypeSupportFactory > command_strTypeSupport;
  //---------------------------------------------------------------
  typedef r_dds::dcps::api::DataReaderTemplate< ::Message::TGenTcrMsg > TGenTcrMsgDataReader;
  typedef r_dds::dcps::api::DataWriterTemplate< ::Message::TGenTcrMsg > TGenTcrMsgDataWriter;

  typedef r_dds::dcps::api::TypeSupportFactoryTemplate<
    ::Message::TGenTcrMsg, 
    ::Message::TGenTcrMsgDataWriter, ::Message::TGenTcrMsgDataReader >  TGenTcrMsgTypeSupportFactory;

  typedef r_dds::dcps::api::TypeSupportTemplate< ::Message::TGenTcrMsg, TGenTcrMsgTypeSupportFactory > TGenTcrMsgTypeSupport;
  //---------------------------------------------------------------
}
#endif
