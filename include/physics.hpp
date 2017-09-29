#ifndef PHYSICS_HPP
#define PHYSICS_HPP

template <class T1, class T2>
bool isIntersecting(const T1& a, const T2& b) noexcept {
	return a.right() >= b.left() && a.left() <= b.right() &&
		a.bottom() >= b.top() && a.top() <= b.bottom();
}

void testCollision(const Paddle& paddle, Ball& ball) noexcept;
void testCollision(Block& block, Ball& ball) noexcept;

#endif // !PHYSICS_HPP
