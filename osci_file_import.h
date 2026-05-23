/*
  ==============================================================================

   This file is part of the osci-render file import module
   Copyright (c) 2026 James H Ball

  ==============================================================================
*/

#pragma once

#include "osci_file_import_config.h"

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                osci_file_import
  vendor:            jameshball
  version:           1.0.0
  name:              osci file import
  description:       Shared file and frame import helpers for osci apps
  website:           https://osci-render.com
  license:           GPLv3
  minimumCppStandard: 20

  dependencies:      juce_core, juce_graphics, juce_gui_basics, juce_audio_basics, juce_audio_formats, osci_render_core

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <osci_render_core/osci_render_core.h>

#include "osci_FrameConsumer.h"
#include "osci_FrameSource.h"
#include "osci_FrameProducer.h"
#include "svg/osci_SvgParser.h"
#include "txt/osci_TextParser.h"
#include "gpla/osci_LineArtParser.h"
#include "wav/osci_WavParser.h"
