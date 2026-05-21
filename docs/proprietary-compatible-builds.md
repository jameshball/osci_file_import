# Proprietary-Compatible Builds

`osci_file_import` contains reusable parser contracts and leaf importers that can be used without the osci-render product orchestration layer.

This is an engineering policy document, not legal advice. The root policy is `../../../docs/proprietary-compatible-builds.md`.

## Build Mode

Set `OSCI_PROPRIETARY_BUILD=1` when compiling a proprietary consumer or verifying that this module avoids incompatible dependencies.

This module should stay focused on import code that:

- is owned, permissively licensed, or covered by compatible inbound rights
- avoids product-only UI and binary resources
- keeps format orchestration in the consuming app
- excludes importers whose authorship, source material, dependencies, or bundled content are not yet cleared

Formats or import paths with unresolved provenance should remain outside this module until they are cleared, separately licensed, or rewritten.

## Dependencies

The module depends on JUCE and `osci_render_core`. A proprietary product still needs suitable JUCE commercial or non-GPL rights.

`OSCI_FILE_IMPORT_ENABLE_FORMATTED_TEXT` controls formatted text import support. It defaults to `OSCI_PREMIUM` for current osci-render products, but reusable consumers can set it directly.

Any future third-party parser dependency must be recorded in a module notice file and reviewed before it is enabled in proprietary-compatible builds.
