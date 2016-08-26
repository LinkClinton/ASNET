```cpp
static const int MaxLights = 16;
//允许的每种种类的光的个数
```
>概述：因为在着色器里面只能声明静态数组以及传给着色器的代码并不能那么很好的
传输任意大小的数据，因此这里限制了16大小

```cpp
		    struct DirLight { //平行光照
		    	DirectX::XMFLOAT4 ambient;  //环境光部分
		    	DirectX::XMFLOAT4 diffuse;  //漫反射光部分
	    		DirectX::XMFLOAT4 specular;  //镜面光部分，第四个是高光部分

	    		DirectX::XMFLOAT3 dir;  //光的方向
				
	    		float			  unsed; //内存对齐的产物
	    	};
		
		    struct PointLight { //点光源
				DirectX::XMFLOAT4 ambient;  //环境光部分
				DirectX::XMFLOAT4 diffuse;  //漫反射光部分
				DirectX::XMFLOAT4 specular;  //镜面光部分，第四个是高光部分

				DirectX::XMFLOAT3 pos;  //光源的位置
				float			  range;  //光照范围

				DirectX::XMFLOAT3 att; //光照的衰减

				float			  unused;  //内存对齐的产物
			};
			
			struct SpotLight { //聚光灯
				DirectX::XMFLOAT4 ambient;  //环境光部分
				DirectX::XMFLOAT4 diffuse; //漫反射光部分
				DirectX::XMFLOAT4 specular; //镜面光部分，第四个是高光部分
				
				DirectX::XMFLOAT3 dir; //光的方向
				float			  range; //光照范围

				DirectX::XMFLOAT3 pos;  //光源位置
				float			  spot; //控制聚光灯的圆锥形大小

				DirectX::XMFLOAT3 att; //光照的衰减
				float		      theta; //内存对齐的产物
			};
```

>概述：3种光源，对其进行定义了，完全可以自己写着色器去对其进行运算，也可以用
BasicEffect类来使用

```cpp
            struct Material {
				DirectX::XMFLOAT4 ambient; //环境光吸收
				DirectX::XMFLOAT4 diffuse;  //漫反射光吸收
				DirectX::XMFLOAT4 specular; //第四个元素是材质光滑
			};
```

>概述：最为基本的材质类型了

```cpp
            //枚举类型，用来设置BasicEffect中的某些效果是否使用
			enum class Enable {
				DirLight,
				SpotLight,
				PointLight,
				Texture
			};

			enum class UnEnable {
				DirLight,
				SpotLight,
				PointLight,
				Texture
			};
```

>概述：固定管道啊啊...

```cpp
            class BasicEffect { //一个效果类，原理就是写了一个着色器而已
			private:
				struct StateEnable {
					int EnableDirLight;
					int EnableSpotLight;
					int EnablePointLight;
					int EnableTexture;
					
					StateEnable();
				};  //效果是否使用的状态，应该是bool类型的
				//但是可怜的16字节大小要求，所以是int

				struct StateLights {
					int DirLightsState;
					int SpotLihtsState;
					int PointLightsState;
					int unused;
					typedef StateLights Collections[16];
					StateLights();
				};
				//每种类型的某一个光照的状态

			private:
				bool                        EffectIsBegin; 
				//EffectBegin在调用后是true，但是在EffectEnd调用后是false
				StateEnable					EffectState;
				//Effect中的效果是否启用的状态
				StateLights::Collections	LightsState;
				//Effect中具体到某个灯光是否启用的状态
				Direct3D::ShaderDataBuffer* EffectStateBuffer;
				Direct3D::ShaderDataBuffer* LightsStateBuffer;
				//常量缓存，用来传给着色器的

				Direct3D::Shader*			EffectShader;
				//着色器
				Direct3D::GraphDirect3D*    ParentGraph;
				//创建其的接口的指针
				void UpdateBufferToShader();
				//将所有的缓存传给着色器
			private:
				Direct3D::DirLight::Collections			DirLights;
				Direct3D::SpotLight::Collections		SpotLights;
				Direct3D::PointLight::Collections		PointLights;
                //灯光
				Direct3D::ShaderDataBuffer*				MaterialBuffer;
				Direct3D::ShaderDataBuffer*				DirLightsBuffer;
				Direct3D::ShaderDataBuffer*             SpotLightsBuffer;
				Direct3D::ShaderDataBuffer*             PointLightsBuffer;
				//缓存
			private:
				Direct3D::ShaderDataBuffer*				EyePosBuffer;
				Direct3D::ShaderDataBuffer*             ProjMatrixBuffer;
				Direct3D::ShaderDataBuffer*             ViewMatrixBuffer;
				Direct3D::ShaderDataBuffer*				WorldMatrixBuffer;
				Direct3D::ShaderDataBuffer*             NormalMatrixBuffer;
                //矩阵缓存
				static DirectX::XMMATRIX Transpose(DirectX::CXMMATRIX matrix);
				//反置矩阵
				static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX matrix);
				//逆反矩阵
			public:
				BasicEffect(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//创建Effect
				~BasicEffect();
				//记得delete
				void Enable(ASNET::Graph::Direct3D::Enable thing);
				//设置某个效果为开启

				void UnEnable(ASNET::Graph::Direct3D::UnEnable thing);
				//设置某个效果为关闭

				void DirLightOn(int which, 
					ASNET::Graph::Direct3D::DirLight dirlight);
				//开启平行光中的某个

				void DirLightOff(int which);
				//关闭平行光中的某个

				void SpotLightOn(int which,
					ASNET::Graph::Direct3D::SpotLight spotlight);
				//开启聚光灯中的某个

				void SpotLightOff(int which);
				//关闭聚光灯中的某个

				void PointLightOn(int which,
					ASNET::Graph::Direct3D::PointLight pointlight);
				//开启点光中的某个

				void PointLightOff(int which);
				//关闭点光中的某个

				void SetMaterial(ASNET::Graph::Direct3D::Material material);
				//设置材质

				void SetTexture(ASNET::Graph::Direct3D::Texture* texture);
				//设置贴图

				void SetProjMatrix(DirectX::CXMMATRIX matrix);
				//设置Proj矩阵

				void SetViewMatrix(DirectX::XMVECTOR eyepos, DirectX::XMVECTOR lookat);
				//设置View矩阵
				
				void SetWorldMatrix(DirectX::CXMMATRIX matrix);
				//设置World矩阵
				
				void EffectBegin(); 
				//如果要使用Effect，要先Begin
				//原理是在使用Begin后设置好自己的着色器
				//将缓存给着色器

				void EffectEnd(); 
				//结束使用Effect，其实就是将着色器设置为原本的
			};

```
>概述：一个简单的着色器的封装吧