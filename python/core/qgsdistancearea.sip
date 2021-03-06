
class QgsDistanceArea
{
%TypeHeaderCode
#include <qgsdistancearea.h>
%End

  public:
    //! Constructor
    QgsDistanceArea();

    //! Destructor
    ~QgsDistanceArea();

    //! Copy constructor
    QgsDistanceArea( const QgsDistanceArea &origDA );

    //! sets whether coordinates must be projected to ellipsoid before measuring
    void setEllipsoidalMode( bool flag );

    //! returns projections enabled flag
    bool ellipsoidalEnabled() const;

    //! sets source spatial reference system (by QGIS CRS)
    void setSourceCrs( long srsid );

    /**
     * Sets source spatial reference system (by QGIS CRS)
     * @note: missing in Python bindings in QGIS < 2.2
     */
    void setSourceCrs( const QgsCoordinateReferenceSystem& srcCRS );

    //! sets source spatial reference system by authid
    void setSourceAuthId( QString authid );

    //! returns source spatial reference system
    long sourceCrs() const;
    //! What sort of coordinate system is being used?
    bool geographic() const;

    //! sets ellipsoid by its acronym
    bool setEllipsoid( const QString& ellipsoid );

    //! Sets ellipsoid by supplied radii
    // Inverse flattening is calculated with invf = a/(a-b)
    bool setEllipsoid( double semiMajor, double semiMinor );

    //! returns ellipsoid's acronym
    const QString& ellipsoid() const;

    //! returns ellipsoid's semi major axis
    double ellipsoidSemiMajor() const;
    //! returns ellipsoid's semi minor axis
    double ellipsoidSemiMinor() const;
    //! returns ellipsoid's inverse flattening
    double ellipsoidInverseFlattening() const;

    //! general measurement (line distance or polygon area)
    double measure( QgsGeometry* geometry );

    //! measures perimeter of polygon
    double measurePerimeter( QgsGeometry* geometry );

    //! measures line
    double measureLine( const QList<QgsPoint>& points );

    /** Measures length of line with one segment
     * @param p1 start of line
     * @param p2 end of line
     * @returns distance in meters, or map units if cartesian calculation was performed
     */
    double measureLine( const QgsPoint& p1, const QgsPoint& p2 );

    /** Measures length of line with one segment and returns units of distance.
     * @param p1 start of line
     * @param p2 end of line
     * @param units will be set to units of measure
     * @returns calculated distance between points. Distance units are stored in units parameter.
     * @note backported from QGIS 2.12 (where it is const)
     * @note not available in python bindings
     */
    // double measureLine( const QgsPoint& p1, const QgsPoint& p2, QGis::UnitType& units );

    //! measures polygon area
    double measurePolygon( const QList<QgsPoint>& points );

    //! compute bearing - in radians
    double bearing( const QgsPoint& p1, const QgsPoint& p2 );

    static QString textUnit( double value, int decimals, QGis::UnitType u, bool isArea, bool keepBaseUnit = false );

    //! Helper for conversion between physical units
    void convertMeasurement( double &measure /In,Out/, QGis::UnitType &measureUnits /In,Out/, QGis::UnitType displayUnits, bool isArea );

  protected:
    //! measures line distance, line points are extracted from WKB
    // @note available in python bindings
    // const unsigned char* measureLine( const unsigned char* feature, double* area, bool hasZptr = false );
    //! measures polygon area and perimeter, vertices are extracted from WKB
    // @note available in python bindings
    // const unsigned char* measurePolygon( const unsigned char* feature, double* area, double* perimeter, bool hasZptr = false );

    /**
      calculates distance from two points on ellipsoid
      based on inverse Vincenty's formulae

      Points p1 and p2 are expected to be in degrees and in currently used ellipsoid

      @note if course1 is not NULL, bearing (in radians) from first point is calculated
            (the same for course2)
      @return distance in meters
     */
    double computeDistanceBearing( const QgsPoint& p1, const QgsPoint& p2,
                                   double* course1 = NULL, double* course2 = NULL );

    //! uses flat / planimetric / Euclidean distance
    double computeDistanceFlat( const QgsPoint& p1, const QgsPoint& p2 );

    //! calculate distance with given coordinates (does not do a transform anymore)
    double computeDistance( const QList<QgsPoint>& points );

    /**
     calculates area of polygon on ellipsoid
     algorithm has been taken from GRASS: gis/area_poly1.c

    */
    double computePolygonArea( const QList<QgsPoint>& points );

    double computePolygonFlatArea( const QList<QgsPoint>& points );

    /**
      precalculates some values
      (must be called always when changing ellipsoid)
    */
    void computeAreaInit();

};
