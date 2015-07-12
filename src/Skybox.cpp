#include "Skybox.hpp"

void Skybox::loadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom)
{
   tTextures[0].loadTexture2D(a_sDirectory+a_sFront);
   tTextures[1].loadTexture2D(a_sDirectory+a_sBack);
   tTextures[2].loadTexture2D(a_sDirectory+a_sLeft);
   tTextures[3].loadTexture2D(a_sDirectory+a_sRight);
   tTextures[4].loadTexture2D(a_sDirectory+a_sTop);
   tTextures[5].loadTexture2D(a_sDirectory+a_sBottom);

   sDirectory = a_sDirectory;

   sFront = a_sFront;
   sBack = a_sBack;
   sLeft = a_sLeft;
   sRight = a_sRight;
   sTop = a_sTop;
   sBottom = a_sBottom;

	for(int i=0; i < 6; i++)
   {
      tTextures[i].setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);
      tTextures[i].setSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      tTextures[i].setSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   }

   glGenVertexArrays(1, &uiVAO);
   glBindVertexArray(uiVAO);

   vboRenderData.createVBO();
   vboRenderData.bindVBO();
}

void Skybox::renderSkybox()
{
   glDepthMask(0);
   glBindVertexArray(uiVAO);
   for(int i=0; i < 6; i++)
   {
      tTextures[i].bindTexture();
      glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
   }
   glDepthMask(1);
}
