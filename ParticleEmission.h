#pragma once
#include "ofGraphics.h"
#include "ofImage.h"
#include "ofVec2f.h"
#include "ofAppRunner.h"
#include "Particle.h"
#include <vector>

class ParticleEmission
{
	private:
		std::vector<Particle> m_particles;
		ofImage m_sprite;
		ofVec2f m_positionOrigin;
		ofVec2f m_direction;
		float m_openAngle;
		float m_maxLifeTime;
		float m_velocity;
		float m_timeSpawnParticle;
		float m_spawnTimeCont;
		bool m_enableParticles;



	public:
		ParticleEmission();
		~ParticleEmission();

		void Setup(ofVec2f origin, ofVec2f direction, float openAngle, float speed, float lifeTime, float timeSpawn, string sprite, float size);
		void Update(ofVec2f position, float deltaTime);
		void SetDirection(ofVec2f newDirection);
		void Draw();
		void CreateParticle();
		void IncreaseOpenAngle();
		void DecreaseOpenAngle();
		void IncreaseSpeedSpawn();
		void DecreaseSpeedSpawn();
		void IncreaseLifeTime();
		void DecreaseLifeTime();
		float GetOpenAngle();
		float GetLifeTime();
		float GetSpawnTime();
		int GetTotalParticle();
		void SetOnOffParticles();
		bool GetOnOffParticles();
};

