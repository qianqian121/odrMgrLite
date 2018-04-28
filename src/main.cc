/* ===================================================
 *  file:       main.cc
 * ---------------------------------------------------
 *  purpose:    main program for testing the
 *              OdrManager
 * ---------------------------------------------------
 *  first edit: 08.07.2006 by M. Dupuis
 * ===================================================
 *  21.07.2008: udate to OpenDRIVE Manager 1.1.19
 *  21.06.2007: udate to OpenDRIVE Manager 1.1.10
 * ===================================================
 */

/* ====== INCLUSIONS ====== */
#include <iostream>
#include <math.h>
#include "OdrManagerLite.hh"
#ifdef LINUX
#include <sys/time.h>
#else
#include <windows.h>
#endif

/* ====== GLOBAL VARIABLES ====== */

int main( int argc, char **argv ) 
{
    OpenDrive::OdrManagerLite myManager;

    if ( argc < 2 ) {
        std::cerr << "Usage: " << std::endl;
        std::cerr << "   odrMgr <filename> <additional filename>" << std::endl;
        exit( -1 );
    }

    std::cerr << "main: analyzing file <" << argv[1] << ">" << std::endl;
        
    if ( !myManager.loadFile( argv[1] ) ) 
    {
        std::cerr << "main: could not load <" << argv[1] << ">" << std::endl;
        exit( 0 );
    }
    
    /********************************************************************
    *                         SAMPLE no. 1
    *                    print the data tree
    *********************************************************************/
    // print the contents of the file
    std::cerr << "main: printing data contents" << std::endl;
    myManager.printData();
        
    /********************************************************************
    *                         SAMPLE no. 3
    *             navigate on the road data, a few samples
    *********************************************************************/
    // create a position object for access to the data/    std::cerr << "main: position tests" << std::endl;
    OpenDrive::Position* myPos= myManager.createPosition();
    
    // activate the position object
    myManager.activatePosition( myPos );
    
    int testCase = 0;
    {
        switch ( testCase )
        {
            case 0: // track to inertial and back
                {
                    for ( double s = 0.0; s < 1600.0; s+= 100.0 ) 
                    {
                        myManager.setTrackPos( 17, s, 3.0 );
                        
                        bool result = myManager.track2inertial();
    
                        fprintf( stderr, "testCase 0: result = %d, s = %.3f, x = %.8lf, y = %.8lf, z = %.8lf, pitch=%.8lf\n", result, s, 
                                          myManager.getInertialPos().getX(), myManager.getInertialPos().getY(), 
                                          myManager.getInertialPos().getZ(), myManager.getInertialPos().getP() );
                       
                        // now the other way round                   
                        result = myManager.inertial2track();
                        myManager.footPoint2inertial();

                        fprintf( stderr, "testCase 0: result = %d, x = %.8lf, y = %.8lf, track = %d, s = %.8lf, t = %.8lf\n", 
                                          result, myManager.getInertialPos().getX(), myManager.getInertialPos().getY(),
                                          myManager.getTrackPos().getTrackId(), myManager.getTrackPos().getS(), myManager.getTrackPos().getT() );
                    }
                }
                break;
		}
	}
	return 1;
}

