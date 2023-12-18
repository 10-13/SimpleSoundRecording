#pragma once
#include "includes.h"
#include "Composition.h"

namespace Music
{
	namespace Styles
	{
		class Electronic : public Composition
		{
		public:
			Electronic() = default;

			Electronic(size_t length, Str name, Str author, Str type, size_t Bpm);

			Str GetType() const;

			size_t GetBPM() const;

			IStr& read(IStr& in) override;

			OStr& print(OStr& out) const override;

		protected:
			Str type_;
			size_t BPM_;
		};

		Electronic::Electronic(size_t length, Str name, Str author, Str type, size_t bpm) : Composition(length, name, author), type_(type), BPM_(bpm) {}

		Str Electronic::GetType() const
		{
			return type_;
		}

		size_t Electronic::GetBPM() const
		{
			return BPM_;
		}

		IStr& Electronic::read(IStr& in)
		{
			Composition::read(in);
			std::getline(in, type_);
			in >> BPM_;
			Str tmp;
			std::getline(in, tmp);
			return in;
		}

		OStr& Electronic::print(OStr& out) const
		{
			Composition::print(out);
			out << type_ << "\n";
			out << BPM_ << "\n";
			return out;
		}
	}
}