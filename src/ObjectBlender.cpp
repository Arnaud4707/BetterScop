#include "../include/ObjectBlender.hpp"

ObjectBlender::ObjectBlender(std::string textObj, std::string textMtl)
{
	std::ifstream file(textObj);
	this->parseLight(textMtl);

	if (!file.is_open())
	{
		std::cout << "Impossible d'ouvrir le fichier: " << textObj << std::endl;;
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::string type;
		std::string x;
		std::string y;
		std::string z;
		std::string w;
		std::stringstream ss(line);
		ss >> type;
		if (type != "v" && type != "f" && type != "o")
			continue;
		if (type == "o")
			ss >> this->name;
		if (type == "v")
		{
			vertex vv;
			ss >> x; ss >> y; ss >> z;
			vv.position.x = std::stof(x);
			vv.position.y = std::stof(y);
			vv.position.z = std::stof(z);
			vv.normal = {0, 0, 0};
			this->vertexs.push_back(vv);
		}
		if (type == "f")
		{
			face ff;
			ss >> x; ss >> y; ss >> z; ss >> w;
			if (!w.empty()){
				ff.x = std::stoi(x) - 1;
				ff.y = std::stoi(y) - 1;
				ff.z = std::stoi(z) - 1;
				this->faces.push_back(ff);
				ff.x = std::stoi(x) - 1;
				ff.y = std::stoi(z) - 1;
				ff.z = std::stoi(w) - 1;
				this->faces.push_back(ff);
			}
			else
			{
				ff.x = std::stoi(x) - 1;
				ff.y = std::stoi(y) - 1;
				ff.z = std::stoi(z) - 1;
				this->faces.push_back(ff);
			}
		}
	}
	file.close();
	this->calculeNormal();
	this->generateTexCoords();
}

// Fonction utilitaire pour parser proprement les blocs "v/vt/vn"
void parseFaceToken(const std::string& token, int& vIdx, int& tIdx, int& nIdx) {
    std::stringstream ss(token);
    std::string v, t, n;

    vIdx = tIdx = nIdx = -1; // Valeurs par défaut si absent

    if (std::getline(ss, v, '/')) {
        if (!v.empty()) vIdx = std::stoi(v) - 1;
    }
    if (std::getline(ss, t, '/')) {
    	if (!t.empty()) tIdx = std::stoi(t) - 1;
    }
    if (std::getline(ss, n, '/')) {
        if (!n.empty()) nIdx = std::stoi(n) - 1;
    }
}

void	ObjectBlender::tri()
{
	vertexs.clear();
	for (auto &f : dfaces){
		vertex vx;
		vertex vy;
		vertex vz;
		vx.position = v[f.position.x];
		vy.position = v[f.position.y];
		vz.position = v[f.position.z];
		vx.normal = n[f.normal.x];
		vy.normal = n[f.normal.y];
		vz.normal = n[f.normal.z];
		vx.texcoord = t[f.texture.x];
		vy.texcoord = t[f.texture.y];
		vz.texcoord = t[f.texture.z];
		vx.idMaterial = f.idMaterial;
		vy.idMaterial = f.idMaterial;
		vz.idMaterial = f.idMaterial;

		vertexs.push_back(vx);
		vertexs.push_back(vy);
		vertexs.push_back(vz);
	}
}

ObjectBlender::ObjectBlender(std::string textObj, std::string textMtl, int d)
{
	(void)d;
    std::ifstream file(textObj);
	this->parseLight(textMtl);

    if (!file.is_open())
    {
        std::cout << "Impossible d'ouvrir le fichier : " << textObj << std::endl;;
        return;
    }

    std::string line;
	key id;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

		if (type == "usemtl")
		{
			ss >> type;
			id.index = type;
			id.nbIndex = (keys.find(type) != keys.end()) ? keys[type] : -1;
		}
        if (type == "o")
        {
            ss >> this->name;
        }
        else if (type == "v")
        {
            vec3 vv;
            ss >> vv.x >> vv.y >> vv.z;
            this->v.push_back(vv);
        }
        else if (type == "vn")
        {
            vec3 vv;
            ss >> vv.x >> vv.y >> vv.z;
            this->n.push_back(vv);
        }
        else if (type == "vt")
        {
            vec2 vv;
            ss >> vv.x >> vv.y;
            this->t.push_back(vv);
        }
        else if (type == "f")
        {
            std::string a, b, c;
            ss >> a >> b >> c;

            dface ff;
            try {
                parseFaceToken(a, ff.position.x, ff.texture.x, ff.normal.x);
                parseFaceToken(b, ff.position.y, ff.texture.y, ff.normal.y);
                parseFaceToken(c, ff.position.z, ff.texture.z, ff.normal.z);
                
				ff.idMaterial = id.nbIndex;
                // IMPORTANT : Ne pas oublier d'ajouter la face au vecteur de la classe !
                this->dfaces.push_back(ff); 
            }
            catch (const std::exception& e) {
                // Évite le crash si le fichier .obj a un format de ligne corrompu
                std::cerr << "Erreur lors du parsing d'une face : " << e.what() << "\n";
            }
        }
    }
    file.close();
	this->tri();
}

ObjectBlender::ObjectBlender(const ObjectBlender& obj){
	this->color = obj.color;
	this->dfaces = obj.dfaces;
	this->faces = obj.faces;
	this->name = obj.name;
	this->vertexs = obj.vertexs;
	this->v = obj.v;
	this->n = obj.n;
	this->t = obj.t;
	this->keys = obj.keys;
	this->light = obj.light;
}

ObjectBlender&	ObjectBlender::operator=(const ObjectBlender& obj){
	if (this == &obj)
		return (*this);
	this->~ObjectBlender();
	*this = ObjectBlender (obj);
	return (*this); 
}

ObjectBlender::~ObjectBlender()
{}

const std::vector<vec3>&	ObjectBlender::getV() const {
	return (this->v);
}

const std::vector<face>&	ObjectBlender::getF() const {
	return (this->faces);
}

const std::vector<dface>&	ObjectBlender::getdF() const {
	return (this->dfaces);
}

const std::vector<vertex>&	ObjectBlender::getVertexs() const {
	return (this->vertexs);
}

const std::string&	ObjectBlender::getName() const {
	return (this->name);
}

const lightning&	ObjectBlender::getlightning() const {
	return (this->light);
}
const std::map<std::string, int>& ObjectBlender::getKey() const {
	return (this->keys);
}

const std::map<int, lightning>& ObjectBlender::getMaterials() const {
	return (this->color);
}

void	ObjectBlender::calculeNormal()
{
	std::vector<vertex> tmp;
	for (face &f : faces)
	{
	    vec3 A = vertexs[f.x].position;
	    vec3 B = vertexs[f.y].position;
	    vec3 C = vertexs[f.z].position;

	    vec3 edge1 = sub(B, A);
	    vec3 edge2 = sub(C, A);

	    vec3 normal = cross(edge1, edge2);

	    vertexs[f.x].normal =
	        add(vertexs[f.x].normal, normal);

	    vertexs[f.y].normal =
	        add(vertexs[f.y].normal, normal);

	    vertexs[f.z].normal =
	        add(vertexs[f.z].normal, normal);
		vertex newVertexX = vertexs[f.x];
		vertex newVertexY = vertexs[f.y];
		vertex newVertexZ = vertexs[f.z];
		tmp.push_back(newVertexX);
		tmp.push_back(newVertexY);
		tmp.push_back(newVertexZ);
	}
	this->vertexs = tmp;

	for (vertex& v : vertexs)
	{
	    v.normal = normalize(v.normal);
	}

	// for (size_t i = 0; i < vertexs.size(); ++i)
	// {
	// 	for (size_t j = i + 1; j < vertexs.size(); ++j)
	// 	{
	// 		if (std::fabs(vertexs[i].position.x - vertexs[j].position.x) < 1e-1 &&
	// 			std::fabs(vertexs[i].position.y - vertexs[j].position.y) < 1e-1 &&
	// 			std::fabs(vertexs[i].position.z - vertexs[j].position.z) < 1e-1)
	// 		{
	// 			vertexs[i].normal = normalize(add(vertexs[i].normal, vertexs[j].normal));
	// 		}
	// 	}
	// }

}

void	ObjectBlender::generateTexCoords()
{
    float minX = vertexs[0].position.x;
    float maxX = vertexs[0].position.x;
    float minZ = vertexs[0].position.z;
    float maxZ = vertexs[0].position.z;

    for (auto &p : vertexs)
    {
        minX = std::min(minX, p.position.x);
        maxX = std::max(maxX, p.position.x);

        minZ = std::min(minZ, p.position.z);
        maxZ = std::max(maxZ, p.position.z);
    }

    float dx = maxX - minX;
    float dz = maxZ - minZ;

    for (auto &vert : vertexs)
    {
        vert.texcoord.x = (vert.position.x - minX) / dx;
        vert.texcoord.y = (vert.position.z - minZ) / dz;
    }
}

void ObjectBlender::parseLight(std::string text)
{
	std::ifstream file(text);

	if (!file.is_open())
	{
		std::cout << "Impossible d'ouvrir le fichier" << text << std::endl;
		return;
	}

	std::string line;
	int i = 0;
	key index;
	while (std::getline(file, line))
	{
		std::string type;
		std::string value;
		std::string x;
		std::string y;
		std::string z;
		std::stringstream ss(line);
		ss >> type;
		if (type != "newmtl" && type != "Ns" && type != "Ka" && type != "Kd" && type != "Ks" && type != "d")
			continue;
		if ( type == "newmtl")
		{
			ss >> index.index;
			index.nbIndex = i;
			keys[index.index] = index.nbIndex;
			i++;
		}
		if (type == "Ns")
		{
			ss >> value;
			this->color[index.nbIndex].shininess = stof(value);
		}
		if (type == "Ks")
		{
			ss >> x; ss >> y; ss >> z;
			this->color[index.nbIndex].specular.x = stof(x);
			this->color[index.nbIndex].specular.y = stof(y);
			this->color[index.nbIndex].specular.z = stof(z);
		}
		if (type == "Ka")
		{
			ss >> x; ss >> y; ss >> z;
			this->color[index.nbIndex].ambient.x = stof(x);
			this->color[index.nbIndex].ambient.y = stof(y);
			this->color[index.nbIndex].ambient.z = stof(z);
		}
		if (type == "Kd")
		{
			ss >> x; ss >> y; ss >> z;
			this->color[index.nbIndex].diffuse.x = stof(x);
			this->color[index.nbIndex].diffuse.y = stof(y);
			this->color[index.nbIndex].diffuse.z = stof(z);
		}
	}
}