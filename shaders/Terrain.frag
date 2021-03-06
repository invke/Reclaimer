#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 mvpMatrix;
uniform mat4 normalMatrix;
uniform vec4 cameraPosition;
uniform vec4 lightPosition;

//in vec4 fragColor;
in vec4 fragPosition;
in vec3 fragNormal;

out vec4 finalColor;


void main() {
    vec4 eyePosition = modelViewMatrix * fragPosition;
    //vec4 eyeCameraPosition = viewMatrix * cameraPosition;
    vec4 eyeLightPosition;
    if (lightPosition.w == 0)
        eyeLightPosition = viewMatrix * normalize(lightPosition);
    else
        eyeLightPosition = viewMatrix * lightPosition;

    vec4 eyeNormal = normalMatrix * vec4(fragNormal, 0.0);

    vec4 materialColor = vec4(0.8, 0.6, 0.5, 1.0);
    //vec3 materialSpecularColor = vec3(1.0);
    float materialShininess = 80.0;

    vec3 ambientColor = vec3(0.1, 0.1, 0.15);
    vec3 diffuseColor = vec3(1.0, 0.95, 0.95);
    vec3 specularColor = vec3(1.0);

    //vec4 normal = normalize(normalMatrix * vec4(fragNormal, 0.0));
    vec4 surfacePosition = modelMatrix * fragPosition;
    vec4 surfaceToCamera = normalize(cameraPosition - surfacePosition);

    vec4 surfaceToLight;
    float attenuation = 1.0;
//    if (lightPosition.w == 0.0) {
//        // direcitonal light
//        //surfaceToLight = normalize(lightPosition);
//        surfaceToLight = viewMatrix * normalize(lightPosition);
//    } else {
//        //surfaceToLight = normalize(lightPosition - surfacePosition);
//        surfaceToLight = viewMatrix * normalize(lightPosition - surfacePosition);
//    }
    vec4 eyeSurfaceToLight = normalize(eyeLightPosition - vec4(eyePosition.xyz, 0.0));

    vec4 viewVector = normalize(vec4(-eyePosition.xyz, 0.0));
    vec4 halfVector = normalize(eyeSurfaceToLight + viewVector);

    // ambient
    vec3 ambient = ambientColor * materialColor.rgb;

    // diffuse
//    float diffuseCoefficient = max(0.0, dot(surfaceToLight, normal));
    float diffuseCoefficient = max(dot(eyeSurfaceToLight, eyeNormal), 0.0);
    vec3 diffuse = materialColor.rgb * diffuseCoefficient;

    // specular
//    float specularCoefficient = 0.0;
    //if (diffuseCoefficient > 0.0)
        //specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
        //specularCoefficient = max(dot(halfVector, eyeNormal), 0);

    float specularCoefficient = max(dot(halfVector, eyeNormal), 0.0);
    vec3 specular = pow(specularCoefficient, materialShininess) * specularColor.rgb;

//    vec3 linearColor = vec3(ambient + attenuation * (diffuse + specular));
    vec3 linearColor = vec3(ambient + attenuation * (diffuse));

    vec3 gamma = vec3(1.0 / 2.2);
    finalColor = vec4(pow(linearColor, gamma), materialColor.a);
//    finalColor = vec4(1.0);
}
