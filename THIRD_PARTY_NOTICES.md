# Third-Party Notices

## tinyobjloader

`osci_file_import` uses tinyobjloader for OBJ parsing through the nested `third_party/tinyobjloader` submodule.

tinyobjloader is licensed under MIT. The bundled source includes its full upstream license in `third_party/tinyobjloader/LICENSE`.

The bundled tinyobjloader source also carries notices for permissive helper code, including mapbox/earcut under ISC and fast_float under its upstream permissive license options. Keep the upstream source notices with distributions that include this module.

## chinese_postman

`osci_file_import` uses chinese-postman path ordering code through the nested `third_party/chinese_postman` submodule.

chinese-postman is licensed under MIT. The bundled source includes its full upstream license in `third_party/chinese_postman/LICENSE`.

## stb_image

PNG/JPEG raster import uses `third_party/stb/stb_image.h`, upstream stb_image 2.30
from https://github.com/nothings/stb at commit
`2c980bb59875b0d32144a71867fbdebb2f77cd20`. Downloaded from the matching
https://raw.githubusercontent.com/nothings/stb/2c980bb59875b0d32144a71867fbdebb2f77cd20/stb_image.h.
The unmodified source contains the complete dual MIT/public-domain license;
this module uses the MIT license option. Only PNG/JPEG support is compiled,
with private symbols, allocation budgets and bounded input callbacks.
Animated GIF uses the module's independently implemented checked parser/LZW
decoder and compositor, not stb_image's animated GIF API.
