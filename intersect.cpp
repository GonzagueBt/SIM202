double ccw(const Point &A, const Point &B, const Point &C)
{
    return (B.x-A.x) * (C.y-A.y) - (C.x-A.x) * (B.y-A.y);
}


// true => AB intersecte CD (marche aussi dans les sens AB DC, BA DC, ...)


bool intersect(const Point &A,  const Point &B, const Point &C, const Point &D)
{
    if ((ccw(A,B,C) > 0 && ccw(A,B,D) < 0) && (ccw(C,D,A) > 0 && ccw(C,D,B) < 0))
        return true;
    else if ((ccw(A,B,C) < 0 && ccw(A,B,D) > 0) && (ccw(C,D,A) > 0 && ccw(C,D,B) < 0))
        return true;
    else if ((ccw(A,B,C) > 0 && ccw(A,B,D) < 0) && (ccw(C,D,A) > 0 && ccw(C,D,B) < 0))
        return true;
    else if ((ccw(A,B,C) > 0 && ccw(A,B,D) < 0) && (ccw(C,D,A) < 0 && ccw(C,D,B) > 0))
        return true;
    else if (ccw(A,B,C) == 0 || ccw(A,B,D) == 0 )
        return true;
    else 
        return false;
}
