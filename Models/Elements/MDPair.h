//
//  MDPair.h
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 05.05.14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef __MDCollisionDetection__MDPair__
#define __MDCollisionDetection__MDPair__

#include <iostream>
#include "MDParticle2D.h"

enum MDBounaries {
    RightBound  = 1,
    LeftBound   = 2,
    TopBound    = 3,
    BottomBound = 4
};

class MDPair {
    
public:
    MDBounaries     Bound;
    MDParticle2D    FirstParticle;
    MDParticle2D    SecondParticle;
    
};

#endif /* defined(__MDCollisionDetection__MDPair__) */
