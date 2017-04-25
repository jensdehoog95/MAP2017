//
//  Flextimer.hpp
//  
//
//  Created by Jens de Hoog on 09/04/2017.
//
//

#ifndef Flextimer_hpp
#define Flextimer_hpp

class Flextimer {
public:
    Flextimer();
    
    void initialize(int modulus);
    void resetCounter();
    void trapCount();
    double getCount();
    
private:
    double counter;
};

#endif /* Flextimer_hpp */
