#include <stdio.h>
#include <assert.h>


#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#define WHITE   1,1,1
#define BLUE    0,0,1
#define RED     1,0,0
#define YELLOW  1,1,0
#define GREEN   0,1,0
#define ORANGE  1,0.4,0
#define ALPHA_BLACK   0,0,0,1
#define PLATFORM_COLOR 0.5,1,0.5,0.8
#define BALL_COLOR 0.5, 1, 0.5
#define CUBE_COLOR 1,1,1,0.5

class Rubik {

    private:
        int Size;
        int AxisBeingRotated = -1; //NO axis is being rotated
        double Rotation = 0; //amount of rotation;
        double Colors[6][9][3] = {
            {{GREEN},{GREEN},{GREEN},{GREEN},{GREEN},{GREEN},{GREEN},{GREEN},{GREEN}}, //FRONT FACE
            {{ORANGE},{ORANGE},{ORANGE},{ORANGE},{ORANGE},{ORANGE},{ORANGE},{ORANGE},{ORANGE}}, //UPPER FACE
            {{BLUE},{BLUE},{BLUE},{BLUE},{BLUE},{BLUE},{BLUE},{BLUE},{BLUE}}, //BACK FACE
            {{RED},{RED},{RED},{RED},{RED},{RED},{RED},{RED},{RED}}, //DOWN FACE
            {{YELLOW},{YELLOW},{YELLOW},{YELLOW},{YELLOW},{YELLOW},{YELLOW},{YELLOW},{YELLOW}}, //LEFT FACE
            {{WHITE},{WHITE},{WHITE},{WHITE},{WHITE},{WHITE},{WHITE},{WHITE},{WHITE}}//RIGHT FACE
        };
        double Edge = 0.02;
        void updateState();
        void copyColors(double source[3], double dest[3]);
        void copyColors(double source1[3], double source2[3], double source3[3], double dest1[3],  double dest2[3],  double dest3[3]);

    public:
        Rubik(int size);
        void draw();
        void update();
};

class Platform {

    //Assumes that it's x=d plane
    private:
        double Size;
        double Z, Y, X;
    public:
        Platform(int size, double x, double z, double y);
        void draw();
        void update(double y, double z);
        double getZ(); double getY(); double getX(); double getSize();
};

class Ball {

    private:
        double Radius;
        double Z, Y, X;
        double SpeedX, SpeedY, SpeedZ;
        bool isDying = false;
        void die();
        double NParticles;
        class Particle *Particles = NULL;
        double DyingParticlesSize = 1.2;
        int DyingParticlesLife = 50;
    public:
        Ball(double size, double x, double z, double y, double speed_x, double speed_y, double speed_z, int n_particles);
        void draw();
        void update(class Cube c, class Platform p);
        bool intersectsUp(class Cube c);
        bool intersectsDown(class Cube c);
        bool intersectsLeft(class Cube c);
        bool intersectsRight(class Cube c);
        bool intersectsFront(class Cube c);
        bool intersectsBack(class Cube c);
        bool intersectsPlatform(class Platform p);
        double getY();
        double getZ();
        double getRadius();

};

class Particle {
    private:
        double Size;
        double X;
        double Y;
        double Z;
        int Life;
        double SpeedX, SpeedY, SpeedZ;
    public:
        Particle(double size, int life, double x, double y, double z);
        void draw();
        void update();
};

class Cube {
    private:
        double Size;
    public:
        Cube(double size);
        void draw();
        void update();
        double getSize();

        void drawLeft();
        void drawRight();
        void drawBack();
        void drawUp();
        void drawDown();

};
/*
 *
 * RayTrace Software Package, release 1.0.4,  February 2004.
 *
 * Author: Samuel R. Buss
 *
 * Software accompanying the book
 *		3D Computer Graphics: A Mathematical Introduction with OpenGL,
 *		by S. Buss, Cambridge University Press, 2003.
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 *   restriction, but if you modify it, please change the filenames to
 *   prevent confusion between different versions.  Please acknowledge
 *   all use of the software in any publications or products based on it.
 *
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
 *
 */

// Include the next line to turn off the routines that use OpenGL
// #define RGBIMAGE_DONT_USE_OPENGL

class RgbImage {
public:
	RgbImage();
	RgbImage( const char* filename );
	RgbImage( int numRows, int numCols );	// Initialize a blank bitmap of this size.
	~RgbImage();

	bool LoadBmpFile( const char *filename );		// Loads the bitmap from the specified file
	bool WriteBmpFile( const char* filename );		// Write the bitmap to the specified file

#ifndef RGBIMAGE_DONT_USE_OPENGL
	bool LoadFromOpenglBuffer();					// Load the bitmap from the current OpenGL buffer
#endif

	long GetNumRows() const { return NumRows; }
	long GetNumCols() const { return NumCols; }
	// Rows are word aligned
	long GetNumBytesPerRow() const { return ((3*NumCols+3)>>2)<<2; }
	const void* ImageData() const { return (void*)ImagePtr; }

	const unsigned char* GetRgbPixel( long row, long col ) const;
	unsigned char* GetRgbPixel( long row, long col );
	void GetRgbPixel( long row, long col, float* red, float* green, float* blue ) const;
	void GetRgbPixel( long row, long col, double* red, double* green, double* blue ) const;

	void SetRgbPixelf( long row, long col, double red, double green, double blue );
	void SetRgbPixelc( long row, long col,
					   unsigned char red, unsigned char green, unsigned char blue );

	// Error reporting. (errors also print message to stderr)
	int GetErrorCode() const { return ErrorCode; }
	enum {
		NoError = 0,
		OpenError = 1,			// Unable to open file for reading
		FileFormatError = 2,	// Not recognized as a 24 bit BMP file
		MemoryError = 3,		// Unable to allocate memory for image data
		ReadError = 4,			// End of file reached prematurely
		WriteError = 5			// Unable to write out data (or no date to write out)
	};
	bool ImageLoaded() const { return (ImagePtr!=0); }  // Is an image loaded?

	void Reset();			// Frees image data memory

private:
	unsigned char* ImagePtr;	// array of pixel values (integers range 0 to 255)
	long NumRows;				// number of rows in image
	long NumCols;				// number of columns in image
	int ErrorCode;				// error code

	static short readShort( FILE* infile );
	static long readLong( FILE* infile );
	static void skipChars( FILE* infile, int numChars );
	static void writeLong( long data, FILE* outfile );
	static void writeShort( short data, FILE* outfile );

	static unsigned char doubleToUnsignedChar( double x );

};

inline RgbImage::RgbImage()
{
	NumRows = 0;
	NumCols = 0;
	ImagePtr = 0;
	ErrorCode = 0;
}

inline RgbImage::RgbImage( const char* filename )
{
	NumRows = 0;
	NumCols = 0;
	ImagePtr = 0;
	ErrorCode = 0;
	LoadBmpFile( filename );
}

inline RgbImage::~RgbImage()
{
	delete[] ImagePtr;
}

// Returned value points to three "unsigned char" values for R,G,B
inline const unsigned char* RgbImage::GetRgbPixel( long row, long col ) const
{
	assert ( row<NumRows && col<NumCols );
	const unsigned char* ret = ImagePtr;
	long i = row*GetNumBytesPerRow() + 3*col;
	ret += i;
	return ret;
}

inline unsigned char* RgbImage::GetRgbPixel( long row, long col )
{
	assert ( row<NumRows && col<NumCols );
	unsigned char* ret = ImagePtr;
	long i = row*GetNumBytesPerRow() + 3*col;
	ret += i;
	return ret;
}

inline void RgbImage::GetRgbPixel( long row, long col, float* red, float* green, float* blue ) const
{
	assert ( row<NumRows && col<NumCols );
	const unsigned char* thePixel = GetRgbPixel( row, col );
	const float f = 1.0f/255.0f;
	*red = f*(float)(*(thePixel++));
	*green = f*(float)(*(thePixel++));
	*blue = f*(float)(*thePixel);
}

inline void RgbImage::GetRgbPixel( long row, long col, double* red, double* green, double* blue ) const
{
	assert ( row<NumRows && col<NumCols );
	const unsigned char* thePixel = GetRgbPixel( row, col );
	const double f = 1.0/255.0;
	*red = f*(double)(*(thePixel++));
	*green = f*(double)(*(thePixel++));
	*blue = f*(double)(*thePixel);
}

inline void RgbImage::Reset()
{
	NumRows = 0;
	NumCols = 0;
	delete[] ImagePtr;
	ImagePtr = 0;
	ErrorCode = 0;
}

#endif
