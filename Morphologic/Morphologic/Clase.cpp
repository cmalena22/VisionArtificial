#include "Header.h"
Morphologic::Morphologic(string path) {
	this->path = path;

}
void Morphologic::OpMorfologicas() {
	Mat radiografia = imread("radiografia.jpg");
	//resize(radiografia, radiografia, Size(), 0.50, 0.50);

	Mat angiografia = imread("angiografia.jpg");
	Mat tacs = imread("tacs.jpg");
	//Erosion
	Mat radiografiaerosion;
	Mat angiografiaErosion;
	Mat tacsErosion;
	//Dilatacion
	Mat radiografiaDilatacion;
	Mat angiografiaDilatacion;
	Mat tacsDilatacion;
	//Top Hat
	Mat radiografiaTop;
	Mat angiografiaTop;
	Mat tacsTop;
	//Black hat
	Mat radiografiaBlack;
	Mat angiografiaBlack;
	Mat tacsBlack;

	Mat restaRadiografia;
	Mat restaAngiografia;
	Mat restaTacs;

	Mat elemento = getStructuringElement(MORPH_CROSS, Size(37, 37), Point(-1, -1));
	morphologyEx(radiografia, radiografiaerosion, MORPH_ERODE, elemento);
	morphologyEx(angiografia, angiografiaErosion, MORPH_ERODE, elemento);
	morphologyEx(tacs, tacsErosion, MORPH_ERODE, elemento);

	morphologyEx(radiografia, radiografiaDilatacion, MORPH_DILATE, elemento);
	morphologyEx(angiografia, angiografiaDilatacion, MORPH_DILATE, elemento);
	morphologyEx(tacs, tacsDilatacion, MORPH_DILATE, elemento);



	morphologyEx(radiografia, radiografiaTop, MORPH_TOPHAT, elemento);
	morphologyEx(angiografia, angiografiaTop, MORPH_TOPHAT, elemento);
	morphologyEx(tacs, tacsTop, MORPH_TOPHAT, elemento);

	morphologyEx(radiografia, radiografiaBlack, MORPH_BLACKHAT, elemento);
	morphologyEx(angiografia, angiografiaBlack, MORPH_BLACKHAT, elemento);
	morphologyEx(tacs, tacsBlack, MORPH_BLACKHAT, elemento);

	absdiff(radiografiaTop, radiografiaBlack, restaRadiografia);
	absdiff(angiografiaTop, angiografiaBlack, restaAngiografia);
	absdiff(tacsTop, tacsBlack, restaTacs);

	Mat totalRadiografia;
	add(radiografia, restaRadiografia, totalRadiografia);
	Mat totalAngiografia;
	add(angiografia, restaAngiografia, totalAngiografia);
	Mat totalTACs;
	add(tacs, restaTacs, totalTACs);

	namedWindow("Radiografia", WINDOW_AUTOSIZE);
	namedWindow("Angiografia", WINDOW_AUTOSIZE);
	namedWindow("TACs", WINDOW_AUTOSIZE);
	namedWindow("Radiografia Erosion", WINDOW_AUTOSIZE);
	namedWindow("Angiografia Erosion", WINDOW_AUTOSIZE);
	namedWindow("TACs Erosion", WINDOW_AUTOSIZE);
	namedWindow("Radiografia Dilatacion", WINDOW_AUTOSIZE);
	namedWindow("Angiografia Dilatacion", WINDOW_AUTOSIZE);
	namedWindow("TACs Dilatacion", WINDOW_AUTOSIZE);
	namedWindow("Radiografia Top", WINDOW_AUTOSIZE);
	namedWindow("Angiografia Top", WINDOW_AUTOSIZE);
	namedWindow("TACs Top", WINDOW_AUTOSIZE);
	namedWindow("Radiografia Black", WINDOW_AUTOSIZE);
	namedWindow("Angiografia Black", WINDOW_AUTOSIZE);
	namedWindow("TACs Black", WINDOW_AUTOSIZE);
	namedWindow("Resta Radiografia", WINDOW_AUTOSIZE);
	namedWindow("Resta angiografia", WINDOW_AUTOSIZE);
	namedWindow("Resta TACs", WINDOW_AUTOSIZE);
	namedWindow("Total Radiografia", WINDOW_AUTOSIZE);
	namedWindow("Total angiografia", WINDOW_AUTOSIZE);
	namedWindow("Total TACs", WINDOW_AUTOSIZE);

	imshow("Radiografia", radiografia);
	imshow("Angiografia", angiografia);
	imshow("TACs", tacs);
	imshow("Radiografia Erosion", radiografiaerosion);
	imshow("Angiografia Erosion", angiografiaErosion);
	imshow("TACs Erosion", tacsErosion);
	imshow("Radiografia Dilatacion", radiografiaDilatacion);
	imshow("Angiografia Dilatacion", angiografiaDilatacion);
	imshow("TACs Dilatacion", tacsDilatacion);
	imshow("Radiografia Top", radiografiaTop);
	imshow("Angiografia Top", angiografiaTop);
	imshow("TACs Top", tacsTop);
	imshow("Radiografia Black", radiografiaBlack);
	imshow("Angiografia Black", angiografiaBlack);
	imshow("TACs Black", tacsBlack);
	imshow("Resta Radiografia", radiografiaBlack);
	imshow("Resta angiografia", angiografiaBlack);
	imshow("Resta TACs", tacsBlack);
	imshow("Total Radiografia", radiografiaBlack);
	imshow("Total angiografia", angiografiaBlack);
	imshow("Total TACs", tacsBlack);
	waitKey(0);
}