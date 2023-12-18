#pragma once

#include "includes.h"

namespace Music
{
	class Composition
	{
	protected:
		size_t length_{ 36000 };

		Str author_{ "10-13" }, name_{ "Dead inside" };

		Composition() = default;

		Composition(size_t l, Str a, Str n);

	public:
		Str GetName() const;

		Str GetAuthor() const;

		size_t GetLength() const;

		size_t GetHours() const;

		size_t GetMinutes() const;

		size_t GetSeconds() const;

		virtual Str GetStyle() const = 0;

		virtual OStr& print(OStr& out) const;

		virtual IStr& read(IStr& in);
	};

	Composition::Composition(size_t l, Str a, Str n) : length_(l), author_(a), name_(n) {}

	Str Composition::GetName() const
	{
		return name_;
	}

	Str Composition::GetAuthor() const
	{
		return author_;
	}

	size_t Composition::GetLength() const
	{
		return length_;
	}

	size_t Composition::GetHours() const
	{
		return length_ / 3600;
	}

	size_t Composition::GetMinutes() const
	{
		return (length_ / 60) % 60;
	}

	size_t Composition::GetSeconds() const
	{
		return length_ % 60;
	}

	OStr& Composition::print(OStr& out) const
	{
		out << length_ << "\n";
		out << author_ << "\n";
		out << name_ << "\n";
		return out;
	}

	IStr& Composition::read(IStr& in)
	{
		in >> length_;
		std::getline(in, author_);  // To read '\n' from row
		std::getline(in, author_);
		std::getline(in, name_);
	}
}