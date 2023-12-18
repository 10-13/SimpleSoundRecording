#pragma once
#include "includes.h"
#include "Composition.h"
#include "Save.h"

namespace Music
{
	class Disk sealed
	{
	public:
		Vec<SPtr<Composition>> Compositions{};

		Disk() = default;

		template <typename T> 
		void AddTrack(T track)
		{
			Compositions.push_back(std::make_shared<T>(track));
		}

		size_t Length() const
		{
			size_t res = 0;
			for (auto& i : Compositions)
			{
				res += i->GetLength();
			}
			return res;
		}

		size_t GetSeconds() const
		{
			return Length() % 60;
		}

		size_t GetMinutes() const
		{
			return (Length() / 60) % 60;
		}

		size_t GetHours() const
		{
			return Length() / 3600;
		}

		Disk SelectByStyle(Str style) const
		{
			Disk res;
			for (auto& i : Compositions)
			{
				if (i->GetStyle() == style)
				{
					res.Compositions.push_back(i);
				}
			}
			return res;
		}

		Disk SelectByLength(size_t min = 0, size_t max = 1'000'000'000) const
		{
			Disk res;
			for (auto& i : Compositions)
			{
				if (i->GetLength() <= max && i->GetLength() >= min)
				{
					res.Compositions.push_back(i);
				}
			}
			return res;
		}

		Disk SelectByStyleLength(Str style, size_t min = 0, size_t max = 1'000'000'000) const
		{
			Disk res;
			for (auto& i : Compositions)
			{
				if (i->GetLength() <= max && i->GetLength() >= min && i->GetStyle() == style)
				{
					res.Compositions.push_back(i);
				}
			}
			return res;
		}

		using CompositionPred = bool (*)(const SPtr<Composition>& comp);

		Disk Select(CompositionPred pred) const
		{
			Disk res;
			for (auto& i : Compositions)
			{
				if (pred(i))
				{
					res.Compositions.push_back(i);
				}
			}
			return res;
		}

		void Shuffle()
		{
			std::random_shuffle(Compositions.begin(), Compositions.end());
		}

		void SortByLength()
		{
			std::sort(Compositions.begin(),
				Compositions.end(),
				[](const SPtr<Composition>& a, const SPtr<Composition>& b) { return a->GetLength() < b->GetLength(); });
		}

		void SortByName()
		{
			std::sort(Compositions.begin(),
				Compositions.end(),
				[](const SPtr<Composition>& a, const SPtr<Composition>& b) { return a->GetName() < b->GetName(); });
		}

		void SortByStyle()
		{
			std::sort(Compositions.begin(),
				Compositions.end(),
				[](const SPtr<Composition>& a, const SPtr<Composition>& b) { return a->GetStyle() < b->GetStyle(); });
		}

		void SortByAuthor()
		{
			std::sort(Compositions.begin(),
				Compositions.end(),
				[](const SPtr<Composition>& a, const SPtr<Composition>& b) { return a->GetAuthor() < b->GetAuthor(); });
		}

		OStr& print(OStr& out)
		{
			out << Compositions.size() << "\n";
			auto saver = Music::Saving::InitializeForMusic();
			for (auto& i : Compositions)
			{
				saver.Write(out, i);
			}
			return out;
		}

		IStr& read(IStr& in)
		{
			size_t sz = 0;
			in >> sz;
			Str tmp;
			std::getline(in, tmp);
			auto saver = Music::Saving::InitializeForMusic();
			while (sz-- > 0)
			{
				Compositions.push_back(saver.Read(in));
			}
			return in;
		}
	};
}