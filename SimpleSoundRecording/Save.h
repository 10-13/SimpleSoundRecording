#pragma once
#include "includes.h"
#include "Composition.h"
#include "Rock.h"
#include "Electronic.h"
#include "Classic.h"
#include <map>

using namespace Music::Styles;

namespace Music
{
	namespace Saving
	{
		template <typename T>
		using GetKeyFunc = Str(*)(const T*);

		template <class SavedType, GetKeyFunc<SavedType> key>
		class Saver
		{
		public:
			using ReadFunc = SPtr<SavedType>(*)(IStr& in);
			using WriteFunc = void(*)(OStr& out, SPtr<SavedType> obj);

			std::map<Str, std::pair<ReadFunc, WriteFunc>> Funcs;

			Saver() {}

			template <typename T>
			void AddType(ReadFunc r, WriteFunc w)
			{
				T a;
				Funcs[key(static_cast<SavedType*>(&a))] = std::make_pair(r, w);
			}

			SPtr<SavedType> Read(IStr& in)
			{
				Str line;
				std::getline(in, line);
				return Funcs[line].first(in);
			}

			void Write(OStr& out, const SPtr<SavedType> obj)
			{
				out << key(&*obj) << "\n";
				Funcs[key(&*obj)].second(out, obj);
			}
		};

		Str GetStyleFromComposition(const Composition* comp)
		{
			return comp->GetStyle();
		}

		template <typename T>
		SPtr<Composition> ReadComp(IStr& in)
		{
			SPtr<T> res = std::make_shared<T>();
			res->read(in);
			return res;
		}

		void WriteComp(OStr& out,const SPtr<Composition> obj)
		{
			obj->print(out);
		}

		Saver<Composition, GetStyleFromComposition> InitializeForMusic()
		{
			Saver<Composition, GetStyleFromComposition> res;
			res.AddType<Rock>(ReadComp<Rock>, WriteComp);
			res.AddType<Electronic>(ReadComp<Electronic>, WriteComp);
			res.AddType<Classic>(ReadComp<Classic>, WriteComp);
			return res;
		}
	}
}
