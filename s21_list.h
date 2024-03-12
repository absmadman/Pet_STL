#ifndef S21_LIST_
#define S21_LIST_

#include <iostream>
#include <memory>
#include <stdexcept>

namespace s21 {

	//node class
	template <typename T>
	class	node {
		public: // ctors dtors
			node() : next_{nullptr}, prev_{nullptr} {}
			node(node *prev, node* next, T& data) {
				if (prev != nullptr) {
					prev->SetNext(this);
				}
				if (next != nullptr) {
					next->SetPrev(this);
				}
				next_ = next;
				prev_ = prev;
				data_ = data;
			}

		public:
			node* GetNext() { return next_; }
			node* GetPrev() { return prev_; }
			void SetNext(node *rhs) {
				next_ = rhs;
			}
			void SetPrev(node *rhs) {
				prev_ = rhs;
			}
			T& GetData() { return data_; }
			T GetData() const { return data_; }

		private:
			T data_;	
			node* next_;
			node* prev_;
	};					// node


	// iterator
	template <typename T>
	class iterator {
		public:
			iterator(node<T> *curr) {
				curr_ = curr;
			}

			iterator(iterator& rhs) {
				curr_ = rhs.GetCurr();
			}
			
		public:
			T& operator*() {
				return curr_->GetData();
			}
			void operator++() {
				CheckForNullptr(curr_->GetNext());
				curr_ = curr_->GetNext();
			}
			void operator--() {
				CheckForNullptr(curr_->GetPrev());
				curr_ = curr_->GetPrev();
			}
			iterator operator+(const int rhs) {
				iterator temp(this);
				for (int i = 0; i < rhs; i++) {
					temp++;
				}
				return temp;
			}
			void operator=(const iterator& rhs) {
				curr_ = rhs.GetCurr();
			}
			node<T>* GetCurr() {
				return curr_;
			}

		private:
			void CheckForNullptr(node<T> *curr) {
				if (!curr) { throw std::invalid_argument("access to non alocate memory"); }
			}
		private:
			node<T>* curr_;

	};					// iterator


	//const_iterator 
	template <typename T>
	class const_iterator : public iterator<T> { // operators не наследуются))))))))())))
		public:
			const_iterator(node<T> *curr) : iterator<T>(curr) {
				curr_ = curr;
			}
			T operator*() {
				return curr_->GetData();
			}

		private:
			node<T>* curr_;
	};					// const_iterator


	//list class
	template <typename T>
	class list {
		public:
			list() { 
				size_ = 0;
				first_ = nullptr;
				last_ = nullptr;
			}

		public:
			void push_back(T data) {
				node<T> *temp = std::move(last_);
				last_ = new node<T>(std::move(temp), nullptr, data);
				if (size_ == 0) {
					first_ = last_;
				}
				//if (temp != nullptr) {
					//temp->SetNext(last_);
				//}
				size_++;
			}
			void push_front(T data) {
				node<T> *temp = std::move(first_);
				first_ = new node<T>(nullptr, std::move(temp), data);
				if (size_ == 0) {
					last_ = first_;
				}
				//if (temp != nullptr) {
					//temp->SetPrev(first_);
				//}
				size_++;
			}
			auto &front() {
				return first_->GetData();
			}
			auto &back() {
				return last_->GetData();
			}
			auto begin() {
				iterator<T> it(first_);
				return it;
			}
			auto end() {
				iterator<T> it(last_);
				return it;
			}
			auto cbegin() {
				const_iterator<T> it(first_);
				return it;
			}
			auto cend() {
				const_iterator<T> it(last_);
				return it;
			}
			int size() {
				return size_;
			}

		private:
			int size_;
			node<T>* first_;
			node<T>* last_;
	};					// list
} // namespace s21
#endif
