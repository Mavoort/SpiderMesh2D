#include <armadillo>
#include <array>
#include <vector>

using point_t = std::array<double, 2>;
using element_t = std::array<double, 3>;

class SpiderMesh {
  public:
	std::ptrdiff_t n_points;
	std::ptrdiff_t n_elements;

	std::vector<point_t> points;
	std::vector<element_t> elements;

	// public member functions
	void addPoint(const point_t& point);
	void addPoint(double x, double y);

  private:
	// member functions
	void insertPoint(const point_t& point);
	void insertPoint(double x, double y);
};
