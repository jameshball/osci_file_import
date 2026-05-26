#pragma once

#include <osci_render_core/osci_render_core.h>

#include <memory>
#include <string>
#include <vector>

class WorldObject {
public:
	WorldObject(const std::string&);

    std::vector<std::unique_ptr<osci::Shape>> draw();
    
    std::vector<osci::Line> edges;
    std::vector<float> vs;
    int numVertices;
};
