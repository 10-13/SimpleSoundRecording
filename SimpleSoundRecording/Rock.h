#pragma once
#include "includes.h"
#include "Composition.h"

namespace Music
{
	namespace Styles
	{
		class Rock : public Composition
		{
		public:
			enum class Type
			{
				Hard	= 'h',
				Soft	= 's',
				Garage	= 'g',
				Punk	= 'p',
				Country = 'c',
				Classic = 's',
			};

			Rock() = default;

			Rock(size_t length, Str name, Str author, Type type);

			Type GetType() const;

			IStr& read(IStr& in) override;

			OStr& print(OStr& out) const override;

			Str GetStyle() const override;

		protected:
			Type type_{Type::Hard};
		};

		Rock::Rock(size_t length, Str name, Str author, Type type) : Composition(length, name, author), type_(type) {}

		Rock::Type Rock::GetType() const
		{
			return type_;
		}

		IStr& Rock::read(IStr& in)
		{
			Composition::read(in);
			Str r;
			std::getline(in, r);
			switch (r[0])
			{
			case static_cast<char>(Rock::Type::Soft):
				type_ = Rock::Type::Soft;
				break;
			case static_cast<char>(Rock::Type::Garage):
				type_ = Rock::Type::Garage;
				break;
			case static_cast<char>(Rock::Type::Punk):
				type_ = Rock::Type::Punk;
				break;
			case static_cast<char>(Rock::Type::Hard):
				type_ = Rock::Type::Hard;
				break;
			case static_cast<char>(Rock::Type::Country):
				type_ = Rock::Type::Country;
				break;
			default:
				type_ = Rock::Type::Classic;
				break;
			}
			return in;
		}

		OStr& Rock::print(OStr& out) const
		{
			Composition::print(out);
			out << static_cast<char>(type_) << '\n';
			return out;
		}

		Str Rock::GetStyle() const
		{
			return "Rock";
		}
	}
}