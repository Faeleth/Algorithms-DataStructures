#define _USE_MATH_DEFINES
#include "math.h"
#include <complex>
#include <iostream>
#include <time.h>

namespace DFT_FFT {

	double check_diff(std::complex<double>* c_DFT, std::complex<double>* c_FFT, int N)
	{
		double sum = 0;
		for (int k{}; k < N; k++){
			sum += std::abs(c_DFT[k] - c_FFT[k]);
		}

		return sum / N;
	}

	std::complex<double>* DFT(double* f, int N)
	{
		std::complex<double>* c = new std::complex<double>[N];
		for (int k{}; k<N; k++){
			for (int n = 0; n < N; n++){
				c[k] += f[n] * std::polar(1.0, -2 * M_PI * k * n/N);
			}
		}
		return c;
	}

	std::complex<double>* FFT(double* f, int N)
	{
		if (N <= 1){
			std::complex<double>* temp = new std::complex<double>[N];
			for (int i{}; i < N; i++){
				temp[i] = f[i];
			}
			return temp;
		}
		
		double* E_temp = new double[N / 2];
		double* O_temp = new double[N / 2];


		for (int i{}, k{}; i < N; i += 2, k++) {
			E_temp[k] = f[i];
			O_temp[k] = f[i + 1];
		}

		std::complex<double>* E = FFT(E_temp, N / 2);
		std::complex<double>* O = FFT(O_temp, N / 2);

		std::complex<double>* ret = new std::complex<double>[N];
		for (int k{}; k < (N / 2); k++){
			std::complex<double> R = std::polar(1.0, -2 * M_PI * k / N);
			ret[k] = E[k] + R*O[k];
			ret[k + N / 2] = E[k] - R * O[k];
		}
		
		delete[]E;
		delete[]O;
		delete[]E_temp;
		delete[]O_temp;
		return ret;
	}

	void timeCompareShowOff(bool printSamples = false)
	{
		srand(time(NULL));
		const int MAX_ORDER = 6; // maksymalny rzad wielkosci danych ( w ramach bazy 2)

		for (int o{}; o <= MAX_ORDER; o++){
			const int N = 1 << o; // rozmiar problemu ( potega dwojki - przesuniecie bitowe w lewo )
			printf("N: % i \n", N);
			double* f = new double[N];
			for (int n = 0; n < N; n++)
				f[n] = n / (double)N; // przykladowe dane ( tu akurat : probki funkcji liniowej )

			// DFT
			clock_t t1 = clock();
			std::complex<double>* cDFT = DFT(f, N);
			clock_t t2 = clock();
			double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
			printf("DFT time[ms] : % f \n", dft_time);

			// FFT
			t1 = clock();
			std::complex<double>* cFFT = FFT(f, N);
			t2 = clock();
			double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
			printf("FFT time[ms] : % f \n", fft_time);
			std::cout << "mean error: " << check_diff(cDFT, cFFT, N) << std::endl;
			
			//Print samples
			if (printSamples)
				for (int k = 0; k < N; k++)	
					printf("DFT: (%.*f  %.*f)\tFFT: (%.*f  %.*f)\n", 4, cDFT[k].real(), 4, cDFT[k].imag(), 4, cFFT[k].real(), 4, cFFT[k].imag());  // wypis na ekran wspolczynnikow obu transformat ( czesci rzeczywiste i urojone )
			printf("------\n");

			delete[] f;
			delete[] cDFT;
			delete[] cFFT;
		}
	}
}