#pragma once
#include "includes.h"
#include "Composition.h"

namespace Music
{
	namespace Styles
	{
		class Classic : public Composition
		{
		public:
			Classic() = default;

			Classic(size_t length, Str name, Str author, Str style, size_t tempo);

			Str GetSubstyle() const;

			size_t GetTempo() const;

			IStr& read(IStr& in) override;

			OStr& print(OStr& out) const override;

			Str GetStyle() const override;

		protected:
			Str style_;
			size_t tempo_;
		};

		Classic::Classic(size_t length, Str name, Str author, Str style, size_t tempo) : Composition(length, name, author), style_(style), tempo_(tempo) {}

		Str Classic::GetSubstyle() const
		{
			return style_;
		}


		size_t Classic::GetTempo() const
		{
			return tempo_;
		}

		IStr& Classic::read(IStr& in)
		{
			Composition::read(in);
			std::getline(in, style_);
			in >> tempo_;
			Str tmp;
			std::getline(in, tmp);
			return in;
		}

		OStr& Classic::print(OStr& out) const
		{
			Composition::print(out);
			out << style_ << "\n";
			out << tempo_ << "\n";
			return out;
		}

		Str Classic::GetStyle() const
		{
			return "Classic";
		}
	}
}