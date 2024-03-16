#ifndef _GLASSBLOCK_INCLUDE
#define _GLASSBLOCK_INCLUDE

#include "DynamicObj.h"

class GlassBlock : public DynamicObj {
public:
    void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, glm::ivec2 sizeObj, int col, ShaderProgram& shaderProgram) override;
    void update(int deltaTime) override;
    void destroy() override;
private:
    bool destroying;
    int color;
    int cdDestroy;

};

#endif
