#include "Cabecera.h"
SalYPimienta::SalYPimienta(string path) {
	this->path = path;

}

int minSal = 0;
double dK;
double dPimienta;
int Pimienta = 0;
int k = 3;
int kImpar = 3;
Mat frame;
Mat gris;
Mat pimienta;

Mat imgFiltroMedia;
Mat imgFiltroGauss;
Mat imgFiltroBlur;
Mat imgFiltroMediaSal;
Mat imgFiltroBlurSal;
Mat imgFiltroGaussSal;

Mat bordeRuidoX;
Mat bordeReducidoX;

Mat bordeRuidoXSal;
Mat bordeReducidoXSal;

Mat cannyImg;
void eventoTrackThresholdSal(int v, void* pP) {
	dK = ((double)minSal) / 10;
	cout << "Nuevo Sal: " << dK << endl;

}

void eventoTrackThresholdPimienta(int v, void* pP) {
	dPimienta = ((double)Pimienta) / 10;

	cout << "Nuevo Pimienta: " << dPimienta << endl;
}


void eventoTrackKernel(int v, void* Pp) {
	if (k % 2 != 0)
		kImpar = k;

}

void SalYPimienta::LecturaVideo() {
	VideoCapture video("prueba.mp4");
	if (video.isOpened()) {

		namedWindow("Video", WINDOW_AUTOSIZE);
		// namedWindow("Mascara", WINDOW_AUTOSIZE

		namedWindow("Sal", WINDOW_AUTOSIZE);
		namedWindow("Pimienta", WINDOW_AUTOSIZE);
		namedWindow("Media", WINDOW_AUTOSIZE);
		namedWindow("Gauss Blur", WINDOW_AUTOSIZE);
		namedWindow("Blur", WINDOW_AUTOSIZE);
		namedWindow("Borde ruido Sal", WINDOW_AUTOSIZE);
		namedWindow("Borde Ruido Reducido", WINDOW_AUTOSIZE);
		namedWindow("Canny", WINDOW_AUTOSIZE);


		createTrackbar("Sal", "Video", &minSal, 10, eventoTrackThresholdSal, NULL);
		createTrackbar("Pimienta", "Video", &Pimienta, 10, eventoTrackThresholdPimienta, NULL);
		createTrackbar("K", "Video", &k, 33, eventoTrackKernel, NULL);
		srand((unsigned)time(0));

		//threshold(resta, resta, 33, 255, THRESH_BINARY);

		while (3 == 3) {
			video >> frame;
			
			if (frame.rows <= 0 || frame.cols <= 0)
				break;
			cvtColor(frame, gris, COLOR_BGR2GRAY);
			cvtColor(frame, pimienta, COLOR_BGR2GRAY);

			//Sal de la imagen

			double porcentaje = dK;
			int total = (porcentaje * ((double)(gris.rows)) * ((double)gris.cols));

			int cont = 0;
			int pixel = 0;
			int fila = 0;
			int col = 0;

			while (cont < total) {
				fila = rand() % gris.rows;
				col = rand() % gris.cols;
				gris.at<uchar>(fila, col) = 255;
				cont++;
			}

			///Pimienta
			
			double porcentajeP = dPimienta;
			int total2 = (porcentajeP * ((double)(pimienta.rows)) * ((double)pimienta.cols));

			int cont2 = 0;
			int fila1 = 0;
			int col2 = 0;

			while (cont2 < total2) {
				fila1 = rand() % pimienta.rows;
				col2 = rand() % pimienta.cols;
				pimienta.at<uchar>(fila1, col2) = 0;
				cont2++;
			}
			//Funcion para filtros Pimienta
			medianBlur(pimienta, imgFiltroMedia, kImpar);			
			GaussianBlur(pimienta, imgFiltroGauss, Size(kImpar, kImpar), 0, 0, 0);
			blur(pimienta, imgFiltroBlur, Size(kImpar, kImpar));

			//Funcion para filtros Sal
			medianBlur(gris, imgFiltroMediaSal, kImpar);
			GaussianBlur(gris, imgFiltroGaussSal, Size(kImpar, kImpar), 0, 0, 0);
			blur(gris, imgFiltroBlurSal, Size(kImpar, kImpar));


			//aplicacion de filtro sobel sobre imagen de ruido pimienta

			Sobel(pimienta,bordeRuidoX,CV_32F,1,0);
			Sobel(imgFiltroMedia, bordeReducidoX, CV_32F, 1, 0);

			Sobel(gris, bordeRuidoXSal, CV_32F, 1, 0);
			Sobel(imgFiltroMediaSal, bordeReducidoXSal, CV_32F, 1, 0);
			
			Mat bordesRuidoReducidoXEntero;
			Mat bordesRuidoXEntero;
			Mat bordesRuidoReducidoXEnteroSal;
			Mat bordesRuidoXEnteroSal;

			convertScaleAbs(bordeRuidoX, bordesRuidoXEntero);
			convertScaleAbs(bordeReducidoX, bordesRuidoReducidoXEntero);
			//aplicacion de filtro sobel sobre imagen de ruido Sal


			convertScaleAbs(bordeRuidoXSal, bordesRuidoXEnteroSal);
			convertScaleAbs(bordeReducidoXSal, bordesRuidoReducidoXEnteroSal);

			// Funcion Canny
			int ratio = 3;
			int minT = 50;
			int maxT = ratio * minT;
			Mat gauss;
			GaussianBlur(gris, gauss, Size(3,3),1.7,1.7);
			// Parámetros: imagen original, imagen resultante, mínimo threshold, máximo threshold y tamaño del kernel
			Canny(gris, cannyImg, minT, maxT, 3);
	

			// Función para escalar una imagen
			resize(frame, frame, Size(), 0.25, 0.25);
			resize(gris, gris, Size(), 0.25, 0.25);
			resize(pimienta, pimienta, Size(), 0.25, 0.25);
			resize(imgFiltroMedia, imgFiltroMedia, Size(), 0.25, 0.25);
			resize(imgFiltroGauss, imgFiltroGauss, Size(), 0.25, 0.25);
			resize(imgFiltroBlur, imgFiltroBlur, Size(), 0.25, 0.25);

			resize(imgFiltroMediaSal, imgFiltroMediaSal, Size(), 0.25, 0.25);
			resize(imgFiltroGaussSal, imgFiltroGaussSal, Size(), 0.25, 0.25);
			resize(imgFiltroBlurSal, imgFiltroBlurSal, Size(), 0.25, 0.25);
			resize(cannyImg, cannyImg, Size(), 0.25, 0.25);

			resize(bordesRuidoXEntero, bordesRuidoXEntero, Size(), 0.25, 0.25);
			resize(bordesRuidoReducidoXEntero, bordesRuidoReducidoXEntero, Size(), 0.25, 0.25);

			resize(bordesRuidoXEnteroSal, bordesRuidoXEnteroSal, Size(), 0.25, 0.25);
			resize(bordesRuidoReducidoXEnteroSal, bordesRuidoReducidoXEnteroSal, Size(), 0.25, 0.25);

			//Visualizacion de imagenes
			imshow("Video", frame);
			imshow("Sal", gris);
			imshow("Pimienta", pimienta);
			imshow("Media", imgFiltroMedia);
			imshow("Gauss Blur", imgFiltroGauss);
			imshow("Blur", imgFiltroBlur);

			imshow("Media Sal", imgFiltroMediaSal);
			imshow("Gauss Blur Sal", imgFiltroGaussSal);
			imshow("Blur Sal", imgFiltroBlurSal);

			imshow("Borde ruido Sal", bordesRuidoXEntero);
			imshow("Borde Ruido Reducido", bordesRuidoReducidoXEntero);
			
			imshow("Borde ruido Sal", bordesRuidoXEnteroSal);
			imshow("Borde Ruido Reducido", bordesRuidoReducidoXEnteroSal);

			imshow("Canny", cannyImg);
		  

			if (waitKey(23) == 27) //Pedimos que espere 23 milisegundos a que el usario presione la tecla escape
				break;
		}
		destroyAllWindows();
	}

}

