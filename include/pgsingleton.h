#ifndef PG_SINGLETON_H
#define PG_SINGLETON_H

template< class T > class PG_Singleton {
public:
	static T& GetInstance() {
		static T obj;
		return obj;
	}

protected:
	PG_Singleton() {
	}
	
	~PG_Singleton() {
	}

private:
	PG_Singleton(const T&);
	T& operator=(const T&);
};

#endif
