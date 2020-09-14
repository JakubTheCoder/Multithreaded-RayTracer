
#ifndef __CGG_MAIN__
#define __CGG_MAIN__



namespace CGG
{
	/// Initialises window to specified size
	/// \return False if something went wrong
	bool Init( int windowWidth, int windowHeight );

	/// Sets every pixel to specified colour
	void SetBackground( int red, int green, int blue );
	
	/// Draws a single pixel to screen. If coordinates are out of bounds, does nothing
	void DrawPixel( int pixelX, int pixelY, int red, int green, int blue );

	/// Displays graphics to screen and keeps window open until user requests exit (pressing escape key or closing window)
	int ShowAndHold();

	/// \return False when user requests program exit
	bool ProcessFrame();

	/// For cleanly shutting down the graphics system
	void Cleanup();

};




#endif
