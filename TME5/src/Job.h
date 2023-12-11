#pragma once
#include "Color.h"
#include "Vec3D.h"
#include "Pool.h"
#include <vector>
#include "Rayon.h"
#include "Barier.h"
#include "Scene.h"

using namespace pr;
Color computeColor(const Sphere & obj, const Rayon & ray, const Vec3D & camera, std::vector<Vec3D> & lights);
int findClosestInter(const Scene & scene, const Rayon & ray);

namespace pr {
using namespace std;
using namespace pr;

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

class DrawPixelJob : public Job {

	Scene &scene;
	Color * pixels;
	vector<Vec3D> &lights;
	int x,y;
	Barrier &barrier;

	public : 
	DrawPixelJob(Scene &s,std::vector<Vec3D> &l, Color *p, int x, int y, Barrier &b) 
	: scene(s), lights(l), pixels(p), x(x), y(y), barrier(b) {}
	void run(){
			Vec3D screenPoint = scene.getScreenPoints()[x][y];
			// le point de l'ecran par lequel passe ce rayon
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);
			int targetSphere = findClosestInter(scene, ray);
			if (targetSphere == -1) {
				// keep background color
				barrier.done();
				return ;
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
				barrier.done();
			}

		}
		~DrawPixelJob() {}
	};

// Job concret : exemple

/**
class SleepJob : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
public :
	SleepJob(int arg, int * ret) : arg(arg), ret(ret) {}
	void run () {
		* ret = calcul(arg);
	}
	~SleepJob(){}
};
**/

}	