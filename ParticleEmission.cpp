#include "ParticleEmission.h"

ParticleEmission::ParticleEmission(){}
ParticleEmission::~ParticleEmission(){}
void ParticleEmission::IncreaseOpenAngle()	{ m_openAngle += 2.0f; };
void ParticleEmission::DecreaseOpenAngle()	{ m_openAngle -= 2.0f; };
void ParticleEmission::IncreaseSpeedSpawn() { m_timeSpawnParticle += 1.0f / 500.0f; };
void ParticleEmission::DecreaseSpeedSpawn() { m_timeSpawnParticle -= 1.0f / 500.0f; };
void ParticleEmission::IncreaseLifeTime()	{ m_maxLifeTime += 0.1f; };
void ParticleEmission::DecreaseLifeTime()	{ m_maxLifeTime -= 0.1f; };
float ParticleEmission::GetOpenAngle()		{ return m_openAngle; };
float ParticleEmission::GetLifeTime()		{ return m_maxLifeTime; };
float ParticleEmission::GetSpawnTime()		{ return m_timeSpawnParticle; };
int ParticleEmission::GetTotalParticle()	{ return m_particles.size();}
void ParticleEmission::SetOnOffParticles() { m_enableParticles = !m_enableParticles; }
bool ParticleEmission::GetOnOffParticles() { return m_enableParticles; }

void ParticleEmission::Setup(ofVec2f origin, ofVec2f direction, float openAngle, float speed, float lifeTime, float timeSpawn, string sprite, float size)
{
	// Inicia os parametros da sistema de particula novo
	m_sprite.loadImage(sprite);
	m_sprite.resize(size, size);
	m_sprite.setAnchorPoint(m_sprite.getWidth() / 2.0f, m_sprite.getHeight() / 2.0f);
	m_positionOrigin = origin;
	SetDirection(direction);
	m_openAngle = openAngle;
	m_maxLifeTime = lifeTime;
	m_velocity = speed;
	m_timeSpawnParticle = timeSpawn;
	m_spawnTimeCont = 0;
	m_enableParticles = true;
}

void ParticleEmission::Update(ofVec2f position, float deltaTime)
{
	if (m_enableParticles) {
		// Atualiza a lista de particulas do sistema de particula, chama o DestroyParticle se a particula atingiu o tempo maximo de vida
		// cria uma nova particula caso o tempo ultrapasse o tempo de spawn
		m_positionOrigin = position;
		m_spawnTimeCont += ofGetLastFrameTime();

		// Cria uma particula
		CreateParticle();
	}

	if (m_particles.size() > 1) {
		// Verifica as particulas que ultrapassaram o tempo maximo de vida e exclui eles do vetor
		std::vector<Particle>::iterator aux;	// Iterator para percorrer a lista de particles

		for (aux = m_particles.begin(); aux < m_particles.end(); aux++) {
			// Atualiza a particula
			aux->Update(m_positionOrigin, deltaTime);

			// Verifica se a particle ultrapassou o tempo de vida, se sim ela eh destruida
			if (!aux->IsLife()) {
				aux = m_particles.erase(aux);
			}
		}
	}

}

void ParticleEmission::SetDirection(ofVec2f newDirection)
{
	// Define uma nova direcao para o emissor de particulas, pode ser usado para mudar a direcao das particulas quando
	// o player virar para outro lado, ou usar o mouse para apontar uma direcao
	m_direction = newDirection;
}

void ParticleEmission::Draw()
{
	if (m_particles.size() > 0) {
		// Percorre a lista de particular desenhando elas
		std::vector<Particle>::iterator aux;	// Iterator para percorrer a lista de particles
		for (aux = m_particles.begin(); aux != m_particles.end(); aux++) {
			aux->Draw(m_sprite, m_positionOrigin);
		}
	}
}

void ParticleEmission::CreateParticle()
{
	// Cria uma particula se ja tiver passado o tempo necessario para criar uma
	if (m_spawnTimeCont > m_timeSpawnParticle) {
		int tmp =  m_spawnTimeCont / m_timeSpawnParticle;
		for (int i = 0; i < tmp; i++) {
			m_particles.push_back(Particle());
			float tmpOP = 90.f + rand() % 165;

			// Inicializa a nova particula criada
			(m_particles.end()-1)->Setup(m_positionOrigin, m_direction, m_openAngle, m_velocity, m_maxLifeTime, tmpOP);

			m_spawnTimeCont -= m_timeSpawnParticle;
		}
	}
}

