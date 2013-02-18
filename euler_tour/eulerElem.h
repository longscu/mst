#ifndef EULERELEM_H
#define EULERELEM_H
#endif

class EulerElem
{
	unsigned int src,dst;
	unsigned int edgeWt;
	unsigned int twinPos;
	unsigned int succ;

public:	
	EulerElem() {
		succ= std::numeric_limits<unsigned int>::max();
	}
	EulerElem(unsigned int src_,unsigned int dst_,unsigned int wt_,unsigned int pos_): src(src_), dst(dst_),edgeWt(wt_), twinPos(pos_) {
		succ= std::numeric_limits<unsigned int>::max();
	} 
	EulerElem(unsigned int src_,unsigned int dst_,unsigned int wt_,unsigned int pos_,unsigned int s): src(src_), dst(dst_),edgeWt(wt_), twinPos(pos_), succ(s) {} 
	
	unsigned int getSrc() const;
	void setSrc(unsigned int src);
	unsigned int getDst() const;
	void setDst(unsigned int dst);
	unsigned int getEdgeWt() const;
	void setEdgeWt(unsigned int wt);
	unsigned int getTwinPos() const;
	void setTwinPos(unsigned int pos);
	unsigned int getSucc() const;
	void setSucc(unsigned int s);

	void swap()
	{
		int temp = src;
		src = dst;
		dst = temp;
		
	}


	
};

//Getters and Setters
unsigned int EulerElem::getSrc() const
{
	return src;
}
void EulerElem::setSrc(unsigned int src)
{
	this->src = src;
}

unsigned int EulerElem::getDst() const
{
	return dst;
}
void EulerElem::setDst(unsigned int dst)
{
	this->dst = dst;
}

unsigned int EulerElem::getEdgeWt() const
{
	return edgeWt;
}
void EulerElem::setEdgeWt(unsigned int wt)
{
	edgeWt = wt;
}

unsigned int EulerElem::getTwinPos() const
{
	return twinPos;
}
void EulerElem::setTwinPos(unsigned int pos)
{
	twinPos = pos;
}

unsigned int EulerElem::getSucc() const
{
	return succ;
}
void EulerElem::setSucc(unsigned int s)
{
	succ = s;
}

//Comparator

struct eulerCmpSrc
{
  	EulerElem min_value() const { 
		return EulerElem(std::numeric_limits<unsigned int>::min(),0,0,0); };
	EulerElem max_value() const { 
		return EulerElem(std::numeric_limits<unsigned int>::max(),0,0,0); };
	bool operator () (const EulerElem &a, const EulerElem &b) const {
		return a.getSrc() < b.getSrc() || (a.getSrc() == b.getSrc() && a.getDst() < b.getDst()) || (a.getSrc() == b.getSrc() && a.getDst() == b.getDst() && a.getEdgeWt() < b.getEdgeWt());
	}
};

struct eulerCmpDst
{
  	EulerElem min_value() const { 
		return EulerElem(0,std::numeric_limits<unsigned int>::min(),0,0); };
	EulerElem max_value() const { 
		return EulerElem(0,std::numeric_limits<unsigned int>::max(),0,0); };
	bool operator () (const EulerElem & a, const EulerElem & b) const {
		return a.getDst() < b.getDst() || (a.getDst() == b.getDst() && a.getSrc() < b.getSrc());
	}
};

struct eulerCmpSucc
{
  	EulerElem min_value() const { 
		return EulerElem(0,0,0,0,std::numeric_limits<unsigned int>::min()); };
	EulerElem max_value() const { 
		return EulerElem(0,0,0,0,std::numeric_limits<unsigned int>::max()); };
	bool operator () (const EulerElem & a, const EulerElem & b) const {
		return a.getSucc() < b.getSucc();
	}
};
