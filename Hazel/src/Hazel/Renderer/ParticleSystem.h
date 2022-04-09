#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Renderer/OrthographicCameraController.h"
namespace Hazel
{
	struct  ParticleProps
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;//�����ٶ������Ӽ��ٶ�
		glm::vec4 ColorBegin,ColorEnd;
		float SizeBegin, SizeEnd, SizeVariation;
		float LifeTime = 1.0f;
	};
	//Ŀǰֻ֧��2D����Ч��������������Ϊ3D����
	class ParticleSystem
	{
	public: 
		ParticleSystem(uint32_t MaxParticle = 100000);
		void OnUpdate(TimeStep ts);
		void OnRender(OrthographicCamera& camera);
		void Emit(const ParticleProps& particleprops);
	private:
		struct  Particle
		{
			glm::vec2 Position;
			glm::vec2 Velocity;
			glm::vec4 ColorBegin, ColorEnd;
			float Rotation = 0.0f;
			float SizeBegin, SizeEnd;

			float LifeTime = 1.0f;
			float LifeRemaining = 0.0f;
			
			bool Active = false;
		};

		//����˼�����ڶ������ӣ����ǲ�����ÿ����Ҫ�������ӵ�ʱ��ȥ���ɣ�������ǰ׼�������ӳأ�����Ҫ��������ʱ���Գ������Ӹ�ֵ
		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex;
		
	
	};
}