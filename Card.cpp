#include <string>
#include "Card.h"

using namespace solitaire;
using namespace Gdiplus;

Card::Card(HWND hwnd, int index, Type type, int x, int y) :
	mHwnd(hwnd), mIndex(index), mType(type), mX(x), mY(y), mIsFront(false)
{
	mBack = std::make_unique<Image>(L"Images/backR.png");

	std::wstring filename;

	switch (mType)
	{
	case Type::Jack:
		filename = L"Images/JH.png";
		break;
	case Type::King:
		filename = L"Images/KD.png";
		break;
	case Type::Queen:
		filename = L"Images/QD.png";
		break;
	}
	mFront = std::make_unique<Image>(filename.c_str());
}

bool Card::CheckClicked(int x, int y)
{
	if (x >= mX && y >= mY && x <= static_cast<UINT>(mX + mFront->GetWidth())
		&& y <= static_cast<UINT>(mY + mFront->GetHeight()))
	{
		Flip(!mIsFront);

		return true;
	}
	return false;
}

void Card::Flip(bool isFront)
{
	mIsFront = isFront;
	Invalidate();
}

void Card::Draw(Gdiplus::Graphics& graphics)
{
	if (mIsFront)
	{
		graphics.DrawImage(mFront.get(), mX, mY, mFront->GetWidth(), mFront->GetHeight());
	}
	else
	{
		graphics.DrawImage(mBack.get(), mX, mY, mBack->GetWidth(), mBack->GetHeight());
	}
}

void Card::Invalidate()
{
	RECT rct{ mX, mY, static_cast<LONG>(mX + mBack->GetWidth()), static_cast<LONG>(mY + mBack->GetHeight()) };

	InvalidateRect(mHwnd, &rct, false);
}