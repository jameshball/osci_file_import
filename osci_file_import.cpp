#include "osci_file_import.h"

#include "osci_FrameProducer.cpp"

#if OSCI_FILE_IMPORT_ENABLE_SVG
#include "svg/osci_SvgParser.cpp"
#endif

#if OSCI_FILE_IMPORT_ENABLE_TXT
#include "txt/osci_TextParser.cpp"
#endif

#if OSCI_FILE_IMPORT_ENABLE_GPLA
#include "gpla/osci_LineArtParser.cpp"
#endif
