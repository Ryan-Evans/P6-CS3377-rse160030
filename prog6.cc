/*
 * Ryan Evans
 * rse160030@utdallas.edu
 * CS 3377.002
 * 
 * prog6.cc
 *
 * Modified from cdkexample.cc by Dr. Perkins
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>


#define MATRIX_WIDTH 3		//modified
#define MATRIX_HEIGHT 5		//modified
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"	//modified

using namespace std;

class BinaryFileHeader
{
public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};

class BinaryFileRecord
{
public:
	uint8_t strLength;
	char stringBuffer[25];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"a" , "a", "b", "c", "d", "e"};	//modified
  const char 		*columnTitles[] = {"a","a", "b", "c"};		//modified
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
//  drawCDKMatrix(myMatrix, true);
  
//  setCDKMatrixCell(myMatrix, 2, 1, "Test Message");
//  BinaryFileHeader magicNumber versionNumber numRecords
//  BinaryFileRecord strLength stringBuffer
	
	ifstream infile("cs3377.bin", ios::binary | ios::in);
	BinaryFileHeader* header = new BinaryFileHeader[1];	
	infile.read((char*)header, sizeof(BinaryFileHeader));
	stringstream sstream;
	sstream << hex << header->magicNumber;
	string magNum ="Magic: 0x" + sstream.str();
	string ver = "Version: " + to_string(header->versionNumber);
	string numRec = "NumRecords: " + to_string(header->numRecords);
	setCDKMatrixCell(myMatrix, 1, 1, magNum.c_str());
	setCDKMatrixCell(myMatrix, 1, 2, ver.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, numRec.c_str());
	drawCDKMatrix(myMatrix, true);


  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
