// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef NOUN_FRAME_CPP
#define NOUN_FRAME_CPP

#include "NounFrame.h"

//-----------------------------------------------------------------------------
//	NounFrame
//-----------------------------------------------------------------------------

void
NounFrame::accept(Visitor & v)
{
	v.visit(*this);
}

//-----------------------------------------------------------------------------

FrameIterator*
NounFrame::begin()
{
	return new NounFrameIterator(this, 0);
}

//-----------------------------------------------------------------------------

FrameIterator*
NounFrame::end()
{
	return new NounFrameIterator(this, -1);
}

//-----------------------------------------------------------------------------

void
NounFrame::setSlot(string s, string f)
{
	// search through the slots to change the specified slot if it
	//	already exists
	bool exists = false;
	for (int k = 0; k < slots.size(); k++)
	{
		if (s == slots[k].name)
		{
			slots[k].value = f;
			exists = true;
			break;
		}
	}

	// didnt exist, so we add it
	if (!exists)
	{
		slot temp(s, f);
		slots.push_back(temp);
	}
}

//-----------------------------------------------------------------------------
//	NounFrameIterator
//-----------------------------------------------------------------------------

NounFrameIterator::NounFrameIterator(NounFrame* cur, int p)
{
	frame = cur;
	pos = p;
}

//-----------------------------------------------------------------------------

NounFrameIterator::~NounFrameIterator()
{

}

//-----------------------------------------------------------------------------

AbstractFrame*
NounFrameIterator::operator*()
{
	if (pos < 0 || pos >= frame->connections.size())
		return 0;
	return frame->connections[pos].af;
}

//-----------------------------------------------------------------------------

const AbstractFrame*
NounFrameIterator::operator*() const
{
	if (pos == -1)
		return 0;
	return frame->connections[pos].af;
}

//-----------------------------------------------------------------------------

FrameIterator&
NounFrameIterator::operator++()
{
	pos++;
	if (pos >= frame->connections.size())
	{
		pos = -1;
	}
	return *this;
}

//-----------------------------------------------------------------------------

AbstractFrame*
NounFrameIterator::getFrame() const
{
	return frame;
}

#endif