#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
	position(Vector2D(100, 100)),
	target(Vector2D(1000, 100)),
	velocity(Vector2D(0, 0)),
	speed(0.5),
	max_force(50),
	mass(0.1),
	max_velocity(200),
	orientation(0),
	sprite_num_frames(0),
	sprite_w(0),
	sprite_h(0),
	draw_sprite(false)
{
}

Agent::Agent(Vector2D veloc) : sprite_texture(0),
	position(Vector2D(100, 100)),
	target(Vector2D(1000, 100)),
	velocity(veloc),
	speed(0.5),
	max_force(50),
	mass(0.1),
	max_velocity(200),
	orientation(0),
	sprite_num_frames(0),
	sprite_w(0),
	sprite_h(0),
	draw_sprite(false)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Agent::SteeringBehavior* Agent::getBehavior() {
	return steering_behaviour;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

Vector2D Agent::getCircleCenter() {
	return circleCenter;
}

std::vector<Agent*> Agent::getNeighbors() {
	return flock;
}

void Agent::setAgents(std::vector<Agent*> agents) {
	flock = agents;
}

void Agent::setCircleCenter(Vector2D circleCenter) {
	this->circleCenter = circleCenter;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

float Agent::getMass()
{
	return mass;
}

void Agent::setMass(float _mass)
{
	mass = _mass;
}

float Agent::getMaxForce()
{
	return max_force;
}

void Agent::setMaxForce(float _force)
{
	max_force = _force;
}

float Agent::getOrientation() {
	return orientation;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void Agent::getDesiredVelocity(Vector2D& desiredVelocityOut, bool seek, float speedFactor) {
	if (seek)
		desiredVelocityOut = target - position;
	else
		desiredVelocityOut = position - target;
	desiredVelocityOut.Normalize();
	desiredVelocityOut *= max_velocity * speedFactor;
}

void Agent::getDistanceToTarget(float& distanceOut) {

	distanceOut = (target - position).Length();
}

void Agent::calculateSpeedFactor(float& speedFactor, float dist, float radius) {
	speedFactor = 1;
	if (dist < radius)
		speedFactor = dist / radius;
}

void Agent::calculateSteeringForce(Vector2D& steeringForce, Vector2D desiredVelocity) {

	vDelta = desiredVelocity - velocity;
	vDelta /= max_velocity;

	steeringForce = vDelta * max_force;
}

void Agent::UpdateForces(Vector2D force, float dtime) {
	// acceleration = force / mass;
	velocity += (force / mass) * dtime;
	velocity.Truncate(max_velocity);
	position += velocity * dtime;
}

<<<<<<< HEAD
=======

bool Agent::getNewPath()
{
	return newPath;
}

void Agent::setNewPath(bool state)
{
	newPath = state;
}

void Agent::setMaxVel(float vel)
{
	max_velocity = vel;
}

>>>>>>> 920fa5520579d91d01aa7e117173c8f9595d3a01
void Agent::setTargetAgent(Agent * target)
{
	targetAgent = target;
}

Agent* Agent::getTargetAgent()
{
	return targetAgent;
}

void Agent::setFlock(std::vector<Agent*> agents) {
	flock = agents;
}
