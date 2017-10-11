#ifndef PHYSICS_HPP
#define PHYSICS_HPP

template <class T1>
bool isIntersecting(const T1& a, const Ball& b) noexcept {
	
	return a.right() >= b.left() && a.left() <= b.right() &&
		a.bottom() >= b.top() && a.top() <= b.bottom();
}

void testCollision(const Paddle& paddle, Ball& ball) noexcept;
void testCollision(Block& block, Ball& ball) noexcept;

#endif // !PHYSICS_HPP
