#pragma once

#include <osci_render_core/osci_render_core.h>

#include <memory>
#include <string>
#include <vector>

class WorldObject {
public:
	// Centred and scaled to fit the screen unless `fit` is false.
	WorldObject(const std::string&, bool fit = true);

    std::vector<std::unique_ptr<osci::Shape>> draw();
    
    std::vector<osci::Line> edges;
    std::vector<float> vs;
    int numVertices;
    // How much fitting scales the vertices, whether or not it did.
    double fitScale = 1;
};
