#include "Defines.h"
struct zzRetarded : player {
	typedef std::vector<state> vst;

	static int x;
	static const unsigned int xxx;
	static const int xxy;

	zzRetarded() {
		x = (int)std::time(NULL);
	}

	template<class tp>
	static inline tp sqr(const tp &x) {
		return x * x;
	}

	static inline bool eql(const state a, const state b) {
		return a == b || a == blank || b == blank;
	}

	static inline bool win(const state a, const state b) {
		if (a == blank)
			return false;
		if (b == blank)
			return true;
		if (b == scissors && a == rock)
			return true;
		if (a == scissors && b == rock)
			return false;
		if (a > b)
			return true;
		return false;
	}

	double init(const vst &h1, const vst &h2) {
		size_t l1 = h1.size();
		size_t l2 = h2.size();
		int r = 0;
		for (size_t u1 = l1 - 1, u2 = l2 - 1, u = 0; u < l1 && u < l2 && u < xxx; --u1, --u2, ++u)
			if (win(h1[u1], h2[u2]))
				++r;
		return (double)r / std::min((size_t)xxx, std::min(l1, l2));
	}

	inline int play01() {
		static int c = 0;
		return c = (c + 1) % 3;
	}

	inline int play02() {
		static int a = 1664525;
		static int b = 1013904223;
		x = x * a + b;
		return std::abs(x % 3);
	}

	int play1(const vst &h1, const vst &h2, const int f) {
		int v1[4] = {};
		for (size_t i = (size_t)std::max((int)h1.size() - xxy, 0); i < h1.size(); ++i)
			++v1[h1[i]];
		int v2[4] = {};
		for (size_t i = (size_t)std::max((int)h2.size() - xxy, 0); i < h2.size(); ++i)
			++v2[h2[i]];
		int u = (int)(std::max_element(v2, v2 + 4) - v2);
		int v = (int)(std::max_element(v1, v1 + 4) - v1);
		u = (u + 1) % 3;
		v = (v + 2) % 3;
		return (f & 1) ? u : v;
	}

	int play2(const vst &h, const int xy, double &rr) {
		//int v[xy];
		vector<int> v;
		v.resize(xy);
		int l = 1;
		v[0] = -1;
		size_t srt = std::max((int)h.size() - xy, 0);
		int j = -1;
		for (size_t i = srt + 1; i < h.size(); ++i) {
			while (j > -1 && !eql(h[srt + j + 1], h[i]))
				j = v[j];
			if (eql(h[srt + j + 1], h[i]))
				++j;
			v[l++] = j;
		}
		if (l - v[l - 1] - 1 == l)
			return 4;
		int k = (h.size() - srt) % (l - 1 - v[l - 1]);
		int u = h[k + srt];
		rr = sqr((double)(l - v[l - 1] - 1)) / (double)k;
		return (u + 1) % 3;
	}

	int doplay(std::size_t tml, const vst &h1, const vst &h2) {
		int uu = play02();
		if (tml * 200000 < sqr(std::min((size_t)xxy, h2.size())))
			return (x & 1) ? play01() : play02();
		double u = init(h1, h2);
		if (u < 0.2)
			return uu;
		int v = 4;
		double w = 0;
		int r = xxy;
		do {
			double x;
			int u = play2(h2, r, x);
			if (x > w) {
				v = u;
				w = x;
			}
			r -= 6;
		} while (r > 1);
		if (v != 4)
			return v;
		if (u > 0.8)
			return play1(h1, h2, 0);
		if (u < 0.4)
			return play1(h1, h2, 1);
		return play1(h1, h2, x & 1);
	}

	virtual state play(std::size_t tml, const vst &h1, const vst &h2) {
		return static_cast<state>(doplay(tml, h1, h2));
	}
};
int zzRetarded::x = 0;
const unsigned int zzRetarded::xxx = 64;
const int zzRetarded::xxy = 48;