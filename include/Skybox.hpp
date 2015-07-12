#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>

using namespace std;

class Skybox
{
public:
   void loadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom);
   void renderSkybox();
   void releaseSkybox();
private:
   uint uiVAO;
   CVertexBufferObject vboRenderData;
   CTexture tTextures[6];
   string sDirectory;
   string sFront, sBack, sLeft, sRight, sTop, sBottom;
};
