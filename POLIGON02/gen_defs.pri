FILENAME = Message

XMLNAME    = $$FILENAME
XMLFILE    = $${PROJECT_PATH}/RDDS_TGenMsg/import/xml/$${XMLNAME}.xml
XMLDIR     = $${PROJECT_PATH}/../import
XML_PRECOMPILER_COMMAND = $$(RDDS_HOME)/bin/XML_DDS_precompiler

INCLUDEPATH += $${XMLDIR}/$${XMLNAME}_DDS/include
INCLUDEPATH += $$(RDDS_HOME)/include/isocpp
INCLUDEPATH += $$(RDDS_HOME)/include/rdds_common

LIBS += -L$$(RDDS_HOME)/bin -lrdds64 -ltransport_base -lpthread -lhasp_linux_x86_64_108836

CONFIG(debug, debug|release) {
    LIBS += -L$${PROJECT_PATH}/RDDS_TGenMsg/bin/debug -lGenTypes
} else {
    LIBS += -L$${PROJECT_PATH}/RDDS_TGenMsg/bin/release -lGenTypes
}

