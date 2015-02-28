#include "Defines.h"
struct daze_player : player
{
	state s;
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		s = state((((0 + std::size_t('d')) * self_history.size() / (opponent_history.size() + std::size_t('a')) + std::size_t('z')) + std::size_t('e') * (self_history.size() ^ opponent_history.size())) % 3);
		return s;
	}
};
