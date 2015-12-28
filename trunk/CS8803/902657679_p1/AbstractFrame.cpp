// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef ABSTRACT_FRAME_CPP
#define ABSTRACT_FRAME_CPP

#include "AbstractFrame.h"

//-----------------------------------------------------------------------------
//	FrameIterator
//-----------------------------------------------------------------------------

bool
FrameIterator::operator==(const FrameIterator & rhs) const
{
	if (this->getFrame() != rhs.getFrame())
		return false;

	return (*(*this) == *rhs);
}

//-----------------------------------------------------------------------------

bool
FrameIterator::operator!=(const FrameIterator & rhs) const
{
	return (*this != rhs);
}

//-----------------------------------------------------------------------------
//	FrameIteratorBridge
//-----------------------------------------------------------------------------

FrameIteratorBridge::FrameIteratorBridge(FrameIterator* iter)
{
	this->iter = iter;
}

//-----------------------------------------------------------------------------

FrameIteratorBridge::~FrameIteratorBridge()
{
	delete iter;
}

//-----------------------------------------------------------------------------

AbstractFrame*
FrameIteratorBridge::operator*()
{
	return **iter;
}

//-----------------------------------------------------------------------------

AbstractFrame*
FrameIteratorBridge::operator*() const
{
	return **iter;
}

//-----------------------------------------------------------------------------

bool
FrameIteratorBridge::operator==(const FrameIteratorBridge & rhs) const
{
	return (*(this->iter) == *(rhs.iter));
}

//-----------------------------------------------------------------------------

bool
FrameIteratorBridge::operator!=(const FrameIteratorBridge & rhs) const
{
	return !(*this == rhs);
}

//-----------------------------------------------------------------------------

FrameIteratorBridge&
FrameIteratorBridge::operator++()
{
	++(*iter);
	return *this;
}

#endif