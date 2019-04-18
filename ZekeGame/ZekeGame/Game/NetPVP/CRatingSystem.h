#pragma once
class CRatingSystem
{
public:
	CRatingSystem();
	~CRatingSystem();
};

static CRatingSystem& RatingSystem() {
	static CRatingSystem rs;
	return rs;
}
