
#ifndef VS_H
#define VS_H

class VertexSet {
public:
	VertexSet(int in) {
		n = in;
		size = 0;
		vertices = new int[n];
	}

	~VertexSet() {
		delete [] vertices;
	}

	int getSize() { return size; }

	int * getVertices() { return vertices; }

	bool contains(int v) {
		for (int i = 0; i < size; i++)
			if (vertices[i] == v) return true;
		return false;
	}

	void insert(int v) {
		vertices[size] = v;
		size++;
	}

private:
	int n;
	int size;
	int * vertices;
};

#endif
