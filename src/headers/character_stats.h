#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

typedef std::uint16_t stattype;

class CharacterStats
{
public:
    explicit CharacterStats(
        const stattype strength = 1u,
        const stattype intellect = 1u,
        const stattype agility = 1u,
        const stattype armor = 0u,
        const stattype resistance = 0u
    ):
    m_strength(strength),
    m_intellect(intellect),
    m_agility(agility),
    m_armor(armor),
    m_resistance(resistance)
    {}

    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const { return m_strength; }

    [[nodiscard]] stattype get_intellect() const { return m_intellect; }

    [[nodiscard]] stattype get_agility() const { return m_agility; }

    [[nodiscard]] stattype get_armor() const { return m_armor; }

    [[nodiscard]] stattype get_resistance() const { return m_resistance; }

protected:
    void increase_stats(
        const stattype strength = 0u,
        const stattype intellect = 0u,
        const stattype agility = 0u
    )
    {
        m_strength += strength;
        m_intellect += intellect;
        m_agility += agility;
    }

private:
    stattype m_strength;
    stattype m_intellect;
    stattype m_agility;
    stattype m_armor;
    stattype m_resistance;
};


class PointStack // I can't stand PointWell, aghrr
{
public:
    PointStack(): m_current(1u), m_initial(1u) {};
    PointStack(const stattype current, const stattype max)
    : m_current(current), m_initial(max)
    {
        if (current > max)
            m_current = max;
    };

    bool set_max(const stattype new_max_points)
    {
        if (new_max_points < 1)
            return false;

        m_initial = new_max_points;

        if (m_current > m_initial)
            m_current = m_initial;

        return true;
    }

    [[nodiscard]] stattype get_initial() const
    {
        return m_initial;
    }

    [[nodiscard]] stattype get_current() const
    {
        return m_current;
    }

    void reduce(const stattype amount)
    {
        if (amount > m_current)
        {
            m_current = 0;
            return;
        }
        m_current -= amount;
    }

    void increase(const stattype amount)
    {
        if (amount + m_current > m_initial)
        {
            m_current = m_initial;
            return;
        }
        m_current += amount;
    }

private:
    stattype m_current;
    stattype m_initial; // stands for MaxHP;
};

#endif //CHARACTER_STATS_H
