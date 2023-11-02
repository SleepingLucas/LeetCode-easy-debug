#pragma once

#include<bits/stdc++.h>
using namespace std;

namespace DEBUG_ {
    /* 打印参数间的间隔符号 */
    std::string SEP = "  "; 
	/* 输出流对象 */
	std::ostream *OUTPUT = &std::cerr;
	/* 是否在新行输出 */
	bool NEWLINE = false;

    /* 判断是否为容器 */
    template<typename T>
    static auto IsIteraber(const T& value) -> decltype((void)std::begin(std::declval<T>()), std::true_type());
    static std::false_type IsIteraber(...);

	/* 重载输出流声明 */
    /* 重载pair */
	template <typename Key, typename Value>
	std::ostream& operator<<(std::ostream&, const std::pair<Key, Value>&);

    /* 重载数组输出 */
	template <unsigned N, typename T, 
	    typename std::enable_if<!std::is_same<T, char>::value>::type*>
	std::ostream& operator<<(std::ostream&, const T(&)[N]);

    /* 重载vector输出 */
    template <typename T>
    std::ostream& operator<<(std::ostream&, const std::vector<T>&);

    /* 重载容器输出 */
    template<typename T,
        typename std::enable_if<decltype(IsIteraber(std::declval<T>()))::value && !std::is_same<T, std::string>::value>::type*>
    std::ostream& operator<<(std::ostream&, const T&);

	/* 重载栈输出 */
	template<typename _Tp, typename _Sequence = deque<_Tp>>
	ostream& operator<<(ostream&, const stack<_Tp, _Sequence>&);

	/* 重载队列输出 */
	template<typename _Tp, typename _Sequence = deque<_Tp>>
	ostream& operator<<(ostream&, const queue<_Tp, _Sequence>&);

	/* 重载优先队列输出 */
	template<typename _Tp, typename _Sequence = vector<_Tp>, typename _Compare  = less<typename _Sequence::value_type> >
	ostream& operator<<(ostream&, const priority_queue<_Tp, _Sequence, _Compare>&);

    /* DEBUG函数声明 */
    /* debug输出数组 */
	template<unsigned N, typename T, typename... Rest, 
	typename std::enable_if<!std::is_same<T, char>::value>::type*>
	void _debug(const char *, const T (&)[N], const Rest &...);

    /* debug输出容器 */
	template<typename First, typename... Rest>
	void _debug(const char *, const First &, const Rest &...);

	/* tuple输出类 */
	template<typename Tuple, size_t N>
	struct tuple_print {
		static void print(const Tuple& t, ostream& os) {
			if constexpr (N > 1) {
				tuple_print<Tuple, N-1>::print(t, os);
				os << "," << get<N-1>(t);
			} else os << get<0>(t);
		}
	};

	/* 重载tuple输出 */
	template<typename... Args>
	ostream& operator<<(ostream& os, const tuple<Args...>& t);

    /* 重载pair输出 */
    template <typename Key, typename Value>
    std::ostream& operator<<(std::ostream& os, const std::pair<Key, Value>& p) {
        os << "<" << p.first << ":" << p.second << ">";
        return os;
    }

	/* 重载数组输出 */
	template<unsigned N, typename T, 
	    typename std::enable_if<!std::is_same<T, char>::value>::type* = nullptr>
	std::ostream& operator<<(std::ostream& os, const T(&arr)[N]) {
		os << "[";
		if (NEWLINE) os << "\n";
		if (!N) os << "]";
		for (unsigned i=0;i<N;i++) {
			os << arr[i] << ",]"[i==N-1];
			if (NEWLINE) os << "\n";
		}
		return os;
	}

	/* 重载vector输出 */
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
		os << "[";
		if (NEWLINE) os << "\n";
		if (v.empty()) os << "]";
		for (auto it = v.begin();it!=v.end();it++) {
			os << *it << ",]"[it==prev(v.end())];
			if (NEWLINE) os << "\n";
		}
		return os;
	}

    /* 重载容器输出 */
    template<typename T,
        typename std::enable_if< decltype(IsIteraber(std::declval<T>()))::value && !std::is_same<T, std::string>::value >::type* = nullptr>
    std::ostream& operator<<(std::ostream &os, const T &value) {
        os << "{";
		if (NEWLINE) os << "\n";
		if (value.empty()) os << "}";
        for (auto it = std::begin(value); it != std::end(value); it++) {
            os << *it << ",}"[next(it) == end(value)];
			if (NEWLINE) os << "\n";
		}
        return os;
    }

	/* 容器适配器输出 */
	/* 自定义栈 */
	template<typename _Tp, typename _Sequence = deque<_Tp> >
	class My_stack: public stack<_Tp, _Sequence> {
	public:
		My_stack(stack<_Tp, _Sequence> _st):stack<_Tp, _Sequence>(_st) {}
		_Sequence& getContainer() {
			return this->c;
		}
	};

	/* 自定义优先队列 */
	template<typename _Tp, typename _Sequence = vector<_Tp>,
		typename _Compare  = less<typename _Sequence::value_type> >
	class My_priority_queue: public priority_queue<_Tp, _Sequence, _Compare> {
	public:
		My_priority_queue(priority_queue<_Tp, _Sequence, _Compare> _pq):priority_queue<_Tp, _Sequence, _Compare>(_pq) {}
		_Sequence& getContainer() {
			return this->c;
		}
	};

	/* 自定义队列 */
	template<typename _Tp, typename _Sequence = deque<_Tp> >
	class My_queue: public queue<_Tp, _Sequence> {
	public:
		My_queue(queue<_Tp, _Sequence> _q):queue<_Tp, _Sequence>(_q) {}
		_Sequence& getContainer() {
			return this->c;
		}
	};

	/* 注册自己的容器适配器 */
	#define DEDINE_CONTAINER_ADAPTER_OBJECT(TypeName, ObjName) My_##TypeName My_##ObjName(ObjName)

	/* 重载栈输出 */
	template<typename _Tp, typename _Sequence>
	ostream& operator<<(ostream& os, const stack<_Tp, _Sequence>& adaptor) {
		DEDINE_CONTAINER_ADAPTER_OBJECT(stack, adaptor);
		os << My_adaptor.getContainer();
		return os;
	}

	/* 重载队列输出 */
	template<typename _Tp, typename _Sequence>
	ostream& operator<<(ostream& os, const queue<_Tp, _Sequence>& adaptor) {
		DEDINE_CONTAINER_ADAPTER_OBJECT(queue, adaptor);
		os << My_adaptor.getContainer();
		return os;
	}

	/* 重载优先队列输出 */
	template<typename _Tp, typename _Sequence, typename _Compare>
	ostream& operator<<(ostream& os, const priority_queue<_Tp, _Sequence, _Compare>& adaptor) {
		DEDINE_CONTAINER_ADAPTER_OBJECT(priority_queue, adaptor);
		os << My_adaptor.getContainer();
		return os;
	}

	/* 重载 tuple 输出 */
	template<typename... Args>
	ostream& operator<<(ostream& os, const tuple<Args...>& t) {
		os << "<";
		tuple_print<decltype(t), sizeof...(Args)>::print(t, os);
		os << ">";
		return os;
	}

	/* 数组特化_debug */
	template<unsigned N, typename T, typename... Rest, 
	    typename std::enable_if<!std::is_same<T, char>::value>::type* = nullptr>
	void _debug(const char *fmt, const T (&first)[N], const Rest &... rest) {
		if constexpr (sizeof...(rest) >= 1) {
			while (*fmt != ',' || *(fmt+1) != ' ') *OUTPUT << *fmt++;
			*OUTPUT << " = " << (NEWLINE? "\n":"") << first << ";" << (NEWLINE? "\n":SEP);
			_debug(fmt + 2, rest...);
		} else *OUTPUT << fmt << " = " << (NEWLINE? "\n":"") << first << '\n';
	}

	/* 容器_debug */
	template<typename First, typename... Rest>
	void _debug(const char *fmt, const First &first, const Rest &... rest) {
		if constexpr (sizeof...(rest) >= 1) {
			while (*fmt != ',' || *(fmt+1) != ' ') *OUTPUT << *fmt++;
			*OUTPUT << " = " << (NEWLINE? "\n":"") << first << ";" << (NEWLINE? "\n":SEP);
			_debug(fmt + 2, rest...);
		} else *OUTPUT << fmt << " = " << (NEWLINE? "\n":"") << first << '\n';
	}

	#define debug(args...) _debug(#args, ##args);
} // namespace DEBUG_