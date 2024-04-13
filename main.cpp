/**
 *	Simple 2D graphics example using MTek-GDL by Lameguy64/TheCodingBrony
 *
 *	This silly little cross-platform example demonstrates loading a couple of
 *	images and then drawing them using Put(), PutX(), and PutS()... It also
 *	demonstrates texture modification by procedurally generating a plasma image
 *	in real-time using PokePixel() (on Wii) or glTexSubImage2D() (on PC).
 *
 */


// Includes for compiling on PC

// Includes for compiling on Wii
#include <mgdl-wii.h>
#include <wiiuse/wpad.h>
#include "game.hpp"

// Prototypes
void init();

// Main function
int main() {

	// Init stuff
	init();

/*


	// Create 3 image objects to load our test images into and one more for our font sheet
	gdl::Image	image[3];
	gdl::Image	fontImage;
	gdl::FFont	font;

	// Some variables
	float angle=0,scaleCount=0;

	// Load the test pictures with linear texture filtering (without mipmaps)

	// My uber-cute Barb fan-art (unless you don't like my style)
	if (!image[0].LoadImageMipmapped("testdata/barb.png", gdl::LN_MM_LN, gdl::Linear, gdl::RGBA8, 9))
		exit(0);

	// Trollface :)
	if (!image[1].LoadImage("testdata/trollface.png", gdl::Linear, gdl::IA4))
		exit(0);


	// Create a 128x128 image for the procedurally generated plasma
	image[2].Create(128, 128, gdl::Linear, gdl::RGBA8);


	// Load generic DOS 8x16 font sheet
	if (!fontImage.LoadImage("testdata/font8x16.png", gdl::Nearest, gdl::I4)) exit(0);

	// Bind font sheet to our font object so we can print with it
	font.BindSheet(fontImage, 8, 16);


	// Generate color table for the plasma effect
	#define J 255.f/360*3
	#define K 255.f/360*2
	#define L 255.f/360*1

	u_int colTable[256];
	for (short c=0; c<256; c++) {

		int r = 255*fabs(sin((J*c)*ROTPI));
		int g = 255*fabs(sin((K*c)*ROTPI));
		int b = 255*fabs(sin((L*c)*ROTPI));

		colTable[c] = RGBA(r, g, b, 255);

    }
	*/

	Game g;
	bool gInit = g.Init();

	// Main loop
	while(1) {

		WPAD_ScanPads();

		// Quit if home button is pressed
		if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME))
			gdl::wii::Exit();

		g.Update();


		// Prepare display for rendering (this must be called prior to intensive code)
		gdl::PrepDisplay();


		g.Draw();

		/*
        for(short py=0; py<128; py++) {
			for(short px=0; px<128; px++) {
				short col = (sin(px*PI/270)*255)+(sin(py*PI/45)*31)+(sin(((py+px)+(4*angle))*PI/90)*63);
				image[2].Texture.PokePixel(px, py, colTable[abs(col)%256]);
			}
		}
		// Flush texture so that updated pixels will be drawn properly
		image[2].Texture.Flush();

		// Stretch the procedurally generated plasma graphic to fill the entire screen
		image[2].PutS(0, 0, gdl::ScreenXres, gdl::ScreenYres, gdl::Color::White);

		// Draw Barb picture and make it roto-zoom
		image[0].PutX(gdl::ScreenCenterX, gdl::ScreenCenterY, gdl::Centered, gdl::Centered, angle, 1.f+(0.8f*(sin(scaleCount*ROTPI))), RGBA(255, 255, 255, 127));

		// Draw trollface and make it bob up & down (for trolliness)
		image[1].Put(16, (gdl::ScreenYres-120)+(16*(sin((scaleCount*32)*ROTPI))) , gdl::Color::White);


		// Draw text and make it scale in and out
		font.DrawText("The power of MTek-GDL!", gdl::Centered, 32, 2.f+(1.f*(sin((scaleCount*4)*ROTPI))), gdl::Color::White);
		*/


		// Display
		gdl::Display();


		// Update counters (with gdl::Delta so that it'll adapt according to your console's current TV system)
		// angle		+= 0.1f*gdl::Delta;
		// scaleCount	+= 0.5f*gdl::Delta;

	}

}

void init() {
	// Initialize the file system, the library, and then Wiimote
	fatInitDefault();
	gdl::InitSystem(gdl::ModeMPAL, gdl::Aspect16x9, gdl::HiRes);
	WPAD_Init();
	// Enter console mode to display error messages (on console platforms only)
	gdl::ConsoleMode();
}
