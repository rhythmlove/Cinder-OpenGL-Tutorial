#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/Rand.h"

#include "cinder/params/Params.h"

// Enable point sprites on OSX
#ifndef GL_POINT_SPRITE_ARB
#define GL_POINT_SPRITE_ARB 0x8861
#endif
#ifndef GL_POINT_FADE_THRESHOLD_SIZE_ARB
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB 0x8128
#endif
#ifndef GL_POINT_SIZE_MIN_ARB
#define GL_POINT_SIZE_MIN_ARB 0x8126
#endif
#ifndef GL_POINT_SIZE_MAX_ARB
#define GL_POINT_SIZE_MIN_ARB 0x8127
#endif
#ifndef GL_VERTEX_PROGRAM_POINT_SIZE
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#endif


using namespace ci;
using namespace ci::app;
using namespace std;

class OpenGlTutorialApp : public App {
public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
  vector<ci::vec3> positions;
  ci::gl::GlslProgRef mShader;
};

void OpenGlTutorialApp::setup()
{
  int distFromCenter = 900;
  for(int i=0; i < 60000; ++i)
  {
    positions.push_back(vec3(-(distFromCenter/2)+randFloat()*distFromCenter,-(distFromCenter/2)+randFloat()*distFromCenter,-(distFromCenter/2)+randFloat()*distFromCenter));
  }
  
  // Load shader programs from our assets folder.
  mShader = gl::GlslProg::create( gl::GlslProg::Format()
                                 .vertex( app::loadAsset( "02/noTransform.vs" ) )
                                 .fragment( app::loadAsset( "02/red.fs" ) ) );
}


void OpenGlTutorialApp::mouseDown( MouseEvent event )
{
  console() << "Working!" << endl;
}

void OpenGlTutorialApp::update()
{
  
}

void OpenGlTutorialApp::draw()
{
  gl::clear(Color(0,0,0));
  gl::enable(GL_POINT_SPRITE_ARB);
  //gl::pointSize(10.0f);
  
  gl::translate( vec3(getWindowWidth()/2,getWindowHeight()/2,0) );
  
  // Use our shader.
  gl::ScopedGlslProg prog( mShader );
  //glPointParameterf( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1.0f );
  //glPointParameterf( GL_POINT_SIZE_MIN_ARB, 0.1f );
 // glPointParameterf( GL_POINT_SIZE_MAX_ARB, 200.0f );
  gl::enable( GL_VERTEX_PROGRAM_POINT_SIZE );   // or use: glEnable
  
  gl::begin(GL_POINTS);
  
  for (std::vector<vec3>::iterator it = positions.begin() ; it != positions.end(); ++it)
  {
    
    vec3 newPos = (vec3)*it;
    //vec3 multiplyPos = newPos*cos(getElapsedSeconds())*1.5;
    gl::vertex(newPos);
  }
  
  gl::end();
  
  gl::translate( vec3(-getWindowWidth()/2,-getWindowHeight()/2,0) );

}

void prepareSettings( App::Settings *settings )
{
  // Tutorial 1: open a window.
  // Cinder handles this one for us. We can set the starting resolution here.
  settings->setWindowSize( 1280, 720 );
  // We can specify whether we want a fullscreen window, too.
  settings->setFullScreen( false );
}


CINDER_APP( OpenGlTutorialApp, RendererGl, prepareSettings )
